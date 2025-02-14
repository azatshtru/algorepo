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

    int visited[vertex_len];
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
                    return 1;
                }
            }
        }
    }
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

    struct vertex* predecessor[vertex_len];
    int max_flow = 0;
    while (graph_edmonds_karp_breadth_first_search(residual_graph, source, sink, predecessor)) {
        max_flow += graph_ford_fulkerson(residual_graph, source, sink, predecessor);
    }

    return max_flow;
}

void graph_network_flow_init_residual_graph(struct graph* graph, struct graph* residual_graph) {
    int vertex_len = graph_vertices_len(graph);
    for(int i = 0; i < vertex_len; i++) {
        graph_add_vertex(residual_graph, vec_get(graph->vertices, i));
    }

    struct edge* edges[graph_edges_len(graph)];
    graph_edges(graph, edges);
    for(int i = 0; i < graph_edges_len(graph); i++) {
        struct edge* edge = edges[i];
        graph_add_edge(residual_graph, edge->from, edge->to, edge->weight);
        graph_add_edge(residual_graph, edge->to, edge->from, 0);
    }
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
        log_label("I have");
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

    int disjoint_paths = graph_max_flow(&split_graph, source, sink);
    free(split_vertices);
    graph_free(&split_graph);

    return disjoint_paths;
}

int graph_max_edge_disjoint_paths(struct graph* graph, void* source, void* sink) {
    return graph_max_flow(graph, source, sink);
}
