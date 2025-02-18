#include "../headers/graph_network_flow.h"
#include "../headers/logging.h"

void network_flow_paths_init(NetworkFlowPaths* paths) {
    *paths = vec_new(vector(void*));
}

vector(void*) network_flow_paths_add(NetworkFlowPaths paths) {
    vector(void*) path = vec_new(void*);
    vec_push(paths, path);
    return path;
}

vector(void*) network_flow_paths_get(NetworkFlowPaths paths, int index) {
    return vec_get(paths, index);
}

void network_flow_paths_free(NetworkFlowPaths paths) {
    for(int i = 0; i < vec_len(paths); i++) {
        vec_free(vec_get(paths, i), NULL);
    }
    vec_free(paths, NULL);
}

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

int graph_max_vertex_disjoint_paths(struct graph* graph, void* source, void* sink, NetworkFlowPaths paths) {
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

    if(paths == NULL) return max_disjoint_paths;

    int visited[vertex_len];
    memzero(visited, sizeof(int) * vertex_len);
    void* path[vertex_len];
    memzero(path, sizeof(void*) * vertex_len);

    VecDeque(struct vertex*) q = queue_new(struct vertex*);

    struct vertex* s = graph_vertex(&split_graph, source);
    visited[graph_vertex_i(graph, source)] = 1;
    path[graph_vertex_i(graph, source)] = source;
    for(int i = 0; i < vec_len(s->out); i++) {
        struct vertex* v = vec_get(s->out, i);
        if(graph_edge_weight(&residual_graph, v->value, s->value)) {
            queue_push_back(q, v);
            path[graph_vertex_i(graph, v->value)] = source;
        }
    }

    void* last_path_vertex[max_disjoint_paths];
    memzero(last_path_vertex, sizeof(void*) * max_disjoint_paths);
    int j = 0;

    while(!queue_is_empty(q)) {
        struct vertex* u = queue_pop_front(q);
        if(u->value == sink) continue;
        struct vertex* split_u = vec_get(u->out, 0);
        if(visited[graph_vertex_i(graph, u->value)]) continue;
        visited[graph_vertex_i(graph, u->value)] = 1;
        for(int i = 0; i < vec_len(split_u->out); i++) {
            struct vertex* v = vec_get(split_u->out, i);
            int flow = graph_edge_weight(&residual_graph, v->value, split_u->value);
            if(flow) {
                if(v->value == sink) {
                    last_path_vertex[j++] = u->value;
                }
                queue_push_back(q, v);
                path[graph_vertex_i(graph, v->value)] = u->value;
            }
        }
    }

    vector(void*) reverse_concatenated_path = vec_new(void*);
    for(int i = 0; i < max_disjoint_paths; i++) {
        int j = graph_vertex_i(graph, last_path_vertex[i]);
        vec_push(reverse_concatenated_path, sink);
        while(path[j] != source) {
            vec_push(reverse_concatenated_path, graph_vertex_from_i(graph, j));
            j = graph_vertex_i(graph, path[j]);
        }
        vec_push(reverse_concatenated_path, graph_vertex_from_i(graph, j));
        vec_push(reverse_concatenated_path, source);
    }
    
    int last = vec_len(reverse_concatenated_path) - 1;
    for(int k = 0; k < max_disjoint_paths; k++) {
        vector(void*) path = network_flow_paths_add(paths);
        void* u = NULL;
        while(u != sink) {
            u = vec_get(reverse_concatenated_path, last);
            vec_push(path, u);
            --last;
        }
    }

    vec_free(reverse_concatenated_path, NULL);
    queue_free(q, NULL);
    graph_free(&split_graph);
    graph_free(&residual_graph);
    free(split_vertices);

    return max_disjoint_paths;
}

int graph_max_edge_disjoint_paths(struct graph* graph, void* source, void* sink, NetworkFlowPaths paths) {
    unsigned int vertex_len = graph_vertices_len(graph);

    struct graph residual_graph = graph_new();
    graph_network_flow_init_residual_graph(graph, &residual_graph);
    int max_disjoint_paths = graph_edmonds_karp(&residual_graph, source, sink);

    if(paths == NULL) return max_disjoint_paths;

    vector(void*) path[vertex_len];
    for(int i = 0; i < vertex_len; i++) {
        path[i] = vec_new(void*);
    }
    VecDeque(struct vertex*) q = queue_new(struct vertex*);

    struct vertex* s = graph_vertex(graph, source);
    queue_push_back(q, s);

    while(!queue_is_empty(q)) {
        struct vertex* u = queue_pop_front(q);
        if(u->value == sink) continue;
        for(int i = 0; i < vec_len(u->out); i++) {
            struct vertex* v = vec_get(u->out, i);
            int flow = graph_edge_weight(&residual_graph, v->value, u->value);
            if(flow && graph_edge_between(&residual_graph, u->value, v->value)) {
                queue_push_back(q, v);
                vec_push(path[graph_vertex_i(graph, v->value)], u->value);
                graph_remove_edge(&residual_graph, u->value, v->value);
            }
        }
    }

    vector(void*) reverse_concatenated_path = vec_new(void*);
    for(int k = 0; k < max_disjoint_paths; k++) {
        void* u = sink;
        vec_push(reverse_concatenated_path, u);
        while(u != source) {
            u = vec_pop(path[graph_vertex_i(graph, u)], -1);
            vec_push(reverse_concatenated_path, u);
        }
    }

    int last = vec_len(reverse_concatenated_path) - 1;
    for(int k = 0; k < max_disjoint_paths; k++) {
        vector(void*) path = network_flow_paths_add(paths);
        void* u = NULL;
        while(u != sink) {
            u = vec_get(reverse_concatenated_path, last);
            vec_push(path, u);
            --last;
        }
    }

    for(int i = 0; i < vertex_len; i++) {
        vec_free(path[i], NULL);
    }
    queue_free(q, NULL);
    return max_disjoint_paths;
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

int graph_minimum_vertex_disjoint_path_cover(struct graph* graph, vector(struct edge*) path_cover) {
    unsigned int vertex_len = graph_vertices_len(graph);
    struct graph matching_graph = graph_new();
    void* duplicates[vertex_len];
    void* source = malloc(1);
    void* sink = malloc(1);
    graph_add_vertex(&matching_graph, source);
    graph_add_vertex(&matching_graph, sink);
    for(int i = 0; i < vertex_len; i++) {
        duplicates[i] = vec_get(graph->vertices, i);
        graph_add_vertex(&matching_graph, duplicates[i]);
        graph_add_vertex(&matching_graph, duplicates+i);
        graph_add_edge(&matching_graph, source, duplicates[i], 1);
        graph_add_edge(&matching_graph, duplicates+i, sink, 1);
    }

    struct edge* edges[graph_edges_len(graph)];
    graph_edges(graph, edges);
    for(int i = 0; i < graph_edges_len(graph); i++) {
        int from = graph_vertex_i(graph, edges[i]->from);
        int to = graph_vertex_i(graph, edges[i]->to);
        graph_add_edge(&matching_graph, duplicates[from], duplicates+to, 1);
    }

    struct graph residual_graph = graph_new();
    graph_network_flow_init_residual_graph(&matching_graph, &residual_graph);
    int maximum_matchings = graph_edmonds_karp(&residual_graph, source, sink);

    for(int i = 0; i < graph_edges_len(graph); i++) {
        struct vertex* from = graph_vertex(graph, edges[i]->from);
        struct vertex* to = graph_vertex(graph, edges[i]->to);
        if(graph_edge_weight(&residual_graph, duplicates+to->i, duplicates[from->i])) {
            vec_push(path_cover, graph_edge_between(graph, from->value, to->value));
        }
    }

    free(source);
    free(sink);
    graph_free(&matching_graph);

    return vertex_len - maximum_matchings;
}

int graph_minimum_vertex_general_path_cover(struct graph* graph, vector(struct edge*) path_cover);
