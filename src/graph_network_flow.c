#include "../headers/graph_network_flow.h"
#include "../headers/logging.h"

int graph_edmonds_karp_breadth_first_search(
    struct graph* residual_graph,
    void* source_ptr,
    void* sink_ptr,
    struct vertex** predecessor
) {
    struct vertex* source = graph_vertex(residual_graph, source_ptr);
    struct vertex* sink = graph_vertex(residual_graph, sink_ptr);

    int vertex_len = graph_vertices_len(residual_graph);

    int* visited = malloc(sizeof(int) * vertex_len);
    memset(visited, 0, sizeof(int) * vertex_len);
    visited[source->i] = 1;
    memset(predecessor, 0, sizeof(struct vertex*) * vertex_len);
    predecessor[source->i] = NULL;

    VecDeque(struct vertex*) q = queue_new(struct vertex*);
    queue_push_back(q, source);

    while(!queue_is_empty(q)) {
        struct vertex* u = queue_pop_front(q);
        for(int i = 0; i < vec_len(u->out); i++) {
            struct vertex* v = vec_get(u->out, i);
            if(!visited[v->i] && graph_edge_weight(residual_graph, u->value, v->value) > 0) {
                queue_push_back(q, v);
                predecessor[v->i] = u;
                visited[v->i] = 1;

                if(v == sink) {
                    queue_free(q, NULL);
                    free(visited);
                    return 1;
                }
            }
        }
    }
    free(visited);
    queue_free(q, NULL);
    return 0;
}

int graph_ford_fulkerson(struct graph* residual_graph, void* source_ptr, void* sink_ptr, struct vertex** predecessor) {
    struct vertex* source = graph_vertex(residual_graph, source_ptr);
    struct vertex* sink = graph_vertex(residual_graph, sink_ptr);

    int path_flow = I32_MAX;

    for (struct vertex* v = sink; v != source; v = predecessor[v->i]) {
        struct vertex* u = predecessor[v->i];
        path_flow =
            path_flow < graph_edge_between(residual_graph, u->value, v->value)->weight
            ? path_flow
            : graph_edge_between(residual_graph, u->value, v->value)->weight;
    }

    for (struct vertex* v = sink; v != source; v = predecessor[v->i]) {
        struct vertex* u = predecessor[v->i];
        graph_edge_between(residual_graph, u->value, v->value)->weight -= path_flow;
        graph_edge_between(residual_graph, v->value, u->value)->weight += path_flow;
    }

    return path_flow;

}

int graph_edmonds_karp(struct graph* residual_graph, void* source, void* sink) {
    int vertex_len = graph_vertices_len(residual_graph);

    struct vertex** predecessor = malloc(sizeof(struct vertex*) * vertex_len);
    int max_flow = 0;
    while (graph_edmonds_karp_breadth_first_search(residual_graph, source, sink, predecessor)) {
        max_flow += graph_ford_fulkerson(residual_graph, source, sink, predecessor);
    }

    free(predecessor);
    return max_flow;
}

void graph_network_flow_init_residual_graph(struct graph* graph, struct graph* residual_graph) {
    int vertex_len = graph_vertices_len(graph);
    for(int i = 0; i < vertex_len; i++) {
        graph_add_vertex(residual_graph, vec_get(graph->vertices, i));
    }

    struct edge** edges = malloc((graph_edges_len(graph) + 0) * sizeof(struct edge*));
    graph_edges(graph, edges);
    for(int i = 0; i < graph_edges_len(graph); i++) {
        struct edge* edge = edges[i];
        graph_add_edge(residual_graph, edge->from, edge->to, edge->weight);
        graph_add_edge(residual_graph, edge->to, edge->from, 0);
    }
    free(edges);
}

int graph_max_flow(struct graph* graph, void* source, void* sink) {
    struct graph residual_graph = graph_new();
    graph_network_flow_init_residual_graph(graph, &residual_graph);

    int max_flow = graph_edmonds_karp(&residual_graph, source, sink);

    graph_free(&residual_graph);
    return max_flow;
}

int graph_min_cut(struct graph* graph, void* source, void* sink, vector(struct edge*) min_cut) {
    int vertex_len = graph_vertices_len(graph);
    struct graph residual_graph = graph_new();
    graph_network_flow_init_residual_graph(graph, &residual_graph);

    int max_flow = graph_edmonds_karp(&residual_graph, source, sink);

    vector(struct vertex*) reachable = vec_new(struct vertex*);
    int visited[vertex_len];
    memzero(visited, sizeof(int) * vertex_len);

    VecDeque(struct vertex*) q = queue_new(struct vertex*);
    queue_push_back(q, graph_vertex(graph, source));

    
    while(!queue_is_empty(q)) {
        struct vertex* u = queue_pop_front(q);
        visited[u->i] = 1;
        vec_push(reachable, u);
        for(int i = 0; i < vec_len(u->out); i++) {
            struct vertex* v = vec_get(u->out, i);
            if(graph_edge_weight(&residual_graph, u->value, v->value) > 0 && !visited[v->i]) {
                queue_push_back(q, v);
            }
        }
    }

    for(int i = 0; i < vec_len(reachable); i++) {
        struct vertex* u = vec_get(reachable, i);
        for(int i = 0; i < vec_len(u->out); i++) {
            struct vertex* v = vec_get(u->out, i);
            if(visited[u->i] && !visited[v->i] && graph_edge_weight(graph, u->value, v->value) > 0) {
                vec_push(min_cut, graph_edge_between(graph, u->value, v->value));
            }
        }
    }
    vec_free(reachable, NULL);
    graph_free(&residual_graph);

    return max_flow;
}

int graph_max_vertex_disjoint_paths(struct graph* graph, void* source, void* sink) {
    int vertex_len = graph_vertices_len(graph);
    char* split_vertices = malloc(vertex_len);
    struct graph split_graph = graph_new();

    graph_add_vertex(&split_graph, source);
    for(int j = 0; j < vec_len(graph_vertex(graph, source)->out); j++) {
        struct vertex* v = vec_get(graph_vertex(graph, source)->out, j);
        graph_add_vertex(&split_graph, v->value);
        graph_add_edge(&split_graph, source, v->value, 1);
    }
    graph_add_vertex(&split_graph, sink);
    for(int j = 0; j < vec_len(graph_vertex(graph, sink)->out); j++) {
        struct vertex* v = vec_get(graph_vertex(graph, sink)->out, j);
        graph_add_vertex(&split_graph, v->value);
        graph_add_edge(&split_graph, sink, v->value, 1);
    }

    for(int i = 0; i < vertex_len; i++) {
        struct vertex* u = graph_vertex(graph, vec_get(graph->vertices, i));
        if(u->value == source || u->value == sink) continue;
        graph_add_vertex(&split_graph, u->value);
        graph_add_vertex(&split_graph, split_vertices+i);
        graph_add_edge(&split_graph, u->value, split_vertices+i, 1);

        for(int j = 0; j < vec_len(u->out); j++) {
            graph_add_vertex(&split_graph, vec_get(u->out, j)->value);
            graph_add_edge(&split_graph, split_vertices+i, vec_get(u->out, j)->value, 1);
        }
    }

    struct graph residual_graph = graph_new();
    graph_network_flow_init_residual_graph(&split_graph, &residual_graph);
    int max_disjoint_paths = graph_edmonds_karp(&residual_graph, source, sink);

    for(int i = 0; i < graph_vertices_len(&split_graph); i++) {
        struct vertex* u = graph_vertex(&split_graph, vec_get(split_graph.vertices, i));
        log_char("I am", *(char*)u->value);
        log_pointer("My address", u->value);
        log_array(vec_as_array(u->out), struct vertex*, vec_len(u->out), x, printf("%p", x->value));
    }

    log_label("\n\n\nfrom here residual begins\n\n");

    for(int i = 0; i < graph_vertices_len(&residual_graph); i++) {
        struct vertex* u = graph_vertex(&residual_graph, vec_get(residual_graph.vertices, i));
        log_char("I am", *(char*)u->value);
        log_pointer("My address", u->value);
        log_array(vec_as_array(u->out), struct vertex*, vec_len(u->out), x, printf("%p", x->value));
    }

    graph_free(&split_graph);
    graph_free(&residual_graph);
    free(split_vertices);

    return max_disjoint_paths;
}

int graph_max_edge_disjoint_paths(struct graph* graph, void* source, void* sink) {
    return graph_max_flow(graph, source, sink);
}

int graph_max_bipartite_matchings(struct graph* graph, vector(struct edge*) matching, vector(void*) minimum_vertex_cover) {
    unsigned int vertex_len = graph_vertices_len(graph);
    Color* color = malloc(sizeof(Color) * vertex_len);
    if(!graph_is_bipartite(graph, color)) return 0;

    struct graph matching_graph = graph_new();
    int* source = malloc(1);
    int* sink = malloc(1);
    graph_add_vertex(&matching_graph, source);
    graph_add_vertex(&matching_graph, sink);


    for(int i = 0; i < vertex_len; i++) {
        void* v = vec_get(graph->vertices, i);
        graph_add_vertex(&matching_graph, v);
        if(color[i] == RED) {
            graph_add_edge(&matching_graph, source, v, 1);
        } 
        if(color[i] == BLUE) {
            graph_add_edge(&matching_graph, v, sink, 1);
        }
    }

    struct edge** edges = malloc(sizeof(struct edge*) * graph_edges_len(graph));
    graph_edges(graph, edges);

    vector(struct edge*) matching_edges = vec_new(struct edge*);
    
    for(int i = 0; i < graph_edges_len(graph); i++) {
        struct edge* e = edges[i];
        if(color[graph_vertex(graph, e->from)->i] == RED) {
            graph_add_edge(&matching_graph, e->from, e->to, 1);
            vec_push(matching_edges, graph_edge_between(&matching_graph, e->from, e->to));
        }
        if(color[graph_vertex(graph, e->to)->i] == RED) {
            graph_add_edge(&matching_graph, e->to, e->from, 1);
            vec_push(matching_edges, graph_edge_between(&matching_graph, e->to, e->from));
        }
    }

    struct graph residual_graph = graph_new();
    graph_network_flow_init_residual_graph(&matching_graph, &residual_graph);

    int maximum_matchings = graph_edmonds_karp(&residual_graph, source, sink);

    int matched[vertex_len];
    memzero(matched, sizeof(int) * vertex_len);

    for(int i = 0; i < vec_len(matching_edges); i++) {
        struct edge* matching_edge = vec_get(matching_edges, i);
        struct edge* residual_edge = graph_edge_between(&residual_graph, matching_edge->from, matching_edge->to);
        if(!residual_edge->weight) {
            matched[graph_vertex(graph, residual_edge->from)->i] = 1;
            struct edge* edge1 = graph_edge_between(graph, residual_edge->from, residual_edge->to);
            struct edge* edge2 = graph_edge_between(graph, residual_edge->to, residual_edge->from);
            vec_push(matching, edge1 ? edge1 : edge2);
        }
    }

    hashset(struct vertex*) vertex_cover = hashset_new(struct vertex*, graph_vertex_hash, graph_vertex_cmp);
    VecDeque(struct vertex*) q = queue_new(struct vertex*);
    int visited[vertex_len];
    memzero(visited, sizeof(int) * vertex_len);

    struct graph undirected = graph_new();
    graph_as_undirected(graph, &undirected);

    for(int i = 0; i < vertex_len; i++) {
        if(color[i] == RED) {
            hashset_insert(vertex_cover, graph_vertex(&undirected, vec_get(undirected.vertices, i)));
        }
    }

    for(int i = 0; i < vertex_len; i++) {
        if(matched[i] || visited[i] || color[i] == BLUE) continue;
        queue_push_back(q, graph_vertex(&undirected, graph_vertex_from_i(&undirected, i)));        
        while(!queue_is_empty(q)) {
            struct vertex* u = queue_pop_front(q);
            if(visited[u->i]) continue;
            visited[u->i] = 1;
            if(color[u->i] == RED) {
                hashset_remove(vertex_cover, u);
            } else if(color[u->i] == BLUE) {
                hashset_insert(vertex_cover, u);
            }
            for(int j = 0; j < vec_len(u->out); j++) {
                struct vertex* v = vec_get(u->out, j);
                queue_push_back(q, v);
            }
        }
    }

    int k = 0;
    for(int i = 0; i < hashset_len(vertex_cover); i++) {
        k = hashset_lazy_iterate(vertex_cover, k);
        vec_push(minimum_vertex_cover, (*vertex_cover)[k]->value);
    }
    

    free(edges);
    free(color);
    free(source);
    free(sink);
    graph_free(&matching_graph);
    graph_free(&residual_graph);
    graph_free(&undirected);
    vec_free(matching_edges, NULL);
    hashset_free(vertex_cover, NULL);
    queue_free(q, NULL);

    return maximum_matchings;
}
