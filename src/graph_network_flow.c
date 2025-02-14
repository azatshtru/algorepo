#include "../headers/graph_network_flow.h"
#include "../headers/logging.h"

int graph_edmonds_karp_breadth_first_search(
    struct graph* residual_graph,
    struct vertex* source,
    struct vertex* sink,
    struct vertex** predecessor
) {
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
            if(!visited[v->i] && graph_edge_weight(residual_graph, u, v) > 0) {
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

int graph_ford_fulkerson(struct graph* residual_graph, struct vertex* source, struct vertex* sink, struct vertex** predecessor) {
    int path_flow = I32_MAX;

    for (struct vertex* v = sink; v != source; v = predecessor[v->i]) {
        struct vertex* u = predecessor[v->i];
        path_flow =
            path_flow < graph_edge_between(residual_graph, u, v)->weight
            ? path_flow
            : graph_edge_between(residual_graph, u, v)->weight;
    }

    for (struct vertex* v = sink; v != source; v = predecessor[v->i]) {
        struct vertex* u = predecessor[v->i];
        graph_edge_between(residual_graph, u, v)->weight -= path_flow;
        graph_edge_between(residual_graph, v, u)->weight += path_flow;
    }

    return path_flow;

}

int graph_edmonds_karp(struct graph* residual_graph, struct vertex* source, struct vertex* sink) {
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
        graph_add_vertex(residual_graph, vec_get(graph->vertices, i)->value);
    }

    struct edge* edges[graph_edges_len(graph)];
    graph_edges(graph, edges);
    for(int i = 0; i < graph_edges_len(graph); i++) {
        struct edge* edge = edges[i];
        graph_add_edge(residual_graph, graph_vertex_from_i(residual_graph, edge->from->i), graph_vertex_from_i(residual_graph, edge->to->i), edge->weight);
        graph_add_edge(residual_graph, graph_vertex_from_i(residual_graph, edge->to->i), graph_vertex_from_i(residual_graph, edge->from->i), 0);
    }
}

int graph_max_flow(struct graph* graph, struct vertex* source, struct vertex* sink) {
    struct graph* residual_graph = graph_new();
    graph_network_flow_init_residual_graph(graph, residual_graph);

    source = vec_get(residual_graph->vertices, source->i);
    sink = vec_get(residual_graph->vertices, sink->i);

    int max_flow = graph_edmonds_karp(residual_graph, source, sink);

    graph_free(residual_graph);
    return max_flow;
}

int graph_min_cut(struct graph* graph, struct vertex* source, struct vertex* sink, vector(struct edge*) min_cut) {
    int vertex_len = graph_vertices_len(graph);
    struct graph* residual_graph = graph_new();
    graph_network_flow_init_residual_graph(graph, residual_graph);
    source = vec_get(residual_graph->vertices, source->i);
    sink = vec_get(residual_graph->vertices, sink->i);

    int max_flow = graph_edmonds_karp(residual_graph, source, sink);

    vector(struct vertex*) reachable = vec_new(struct vertex*);
    int visited[vertex_len];
    memzero(visited, sizeof(int) * vertex_len);


    VecDeque(struct vertex*) q = queue_new(struct vertex*);
    queue_push_back(q, source);
    
    while(!queue_is_empty(q)) {
        struct vertex* u = queue_pop_front(q);
        visited[u->i] = 1;
        vec_push(reachable, graph_vertex_from_i(graph, u->i));
        for(int i = 0; i < vec_len(u->out); i++) {
            struct vertex* v = vec_get(u->out, i);
            if(graph_edge_weight(residual_graph, u, v) > 0 && !visited[v->i]) {
                queue_push_back(q, v);
            }
        }
    }

    for(int i = 0; i < vec_len(reachable); i++) {
        struct vertex* u = vec_get(reachable, i);
        for(int i = 0; i < vec_len(u->out); i++) {
            struct vertex* v = vec_get(u->out, i);
            if(visited[u->i] && !visited[v->i] && graph_edge_weight(graph, u, v) > 0) {
                vec_push(min_cut, graph_edge_between(graph, u, v));
            }
        }
    }
    vec_free(reachable, NULL);
    graph_free(residual_graph);

    return max_flow;
}

int graph_max_node_disjoint_paths(struct graph* graph, struct vertex* source, struct vertex* sink) {
    return 0;
}
