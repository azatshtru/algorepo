#include "../headers/graph_network_flow.h"

int ford_fulkerson_flow_cmp(void* a, void* b) {
    struct ford_fulkerson_flow* flow_1 = ((struct ford_fulkerson_flow*)a);
    struct ford_fulkerson_flow* flow_2 = ((struct ford_fulkerson_flow*)b);
    return flow_1->from == flow_2->from && flow_1->to == flow_2->to;
}

unsigned int ford_fulkerson_flow_hash(void* a) {
    struct ford_fulkerson_flow* flow = ((struct ford_fulkerson_flow*)a);
    return cantor_pairing(flow->from->i, flow->to->i);
}

int graph_edmonds_karp_breadth_first_search(
    struct graph* residual_graph,
    struct vertex* source,
    struct vertex* sink,
    struct vertex** predecessor
) {
    int vertex_len = graph_vertices_len(residual_graph);

    int visited[vertex_len];
    memzero(visited, sizeof(int) * vertex_len);
    visited[source->i] = 1;
    predecessor[source->i] = NULL;

    VecDeque(struct vertex*) q = queue_new(struct vertex*);
    queue_push_back(q, source);

    while(!queue_is_empty(q)) {
        struct vertex* current = queue_pop_front(q);
        for(int i = 0; i < vec_len(current->out); i++) {
            struct vertex* u = vec_get(current->out, i);
            if(!visited[u->i] && graph_edge_between(residual_graph, current->value, u->value) > 0) {
                queue_push_back(q, u);
                predecessor[u->i] = current;
                visited[u->i] = 1;

                if(u == sink) {
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

int graph_edmonds_karp(struct graph* graph, struct vertex* source, struct vertex* sink) {
    int vertex_len = graph_vertices_len(graph);
    struct vertex* predecessor[vertex_len];

    struct graph residual_graph = graph_new();
    for(int i = 0; i < vertex_len; i++) {
        graph_add_vertex(&residual_graph, vec_get(graph->vertices, i));
    }

    struct edge* edges[graph_edges_len(graph)];
    graph_edges(graph, edges);
    for(int i = 0; i < graph_edges_len(graph); i++) {
        struct edge* edge = edges[i];
        graph_add_edge(&residual_graph, edge->from, edge->to, edge->weight);
        graph_add_edge(&residual_graph, edge->to, edge->from, 0);
    }

    int max_flow = 0;
    while (graph_edmonds_karp_breadth_first_search(&residual_graph, source, sink, predecessor)) {
        max_flow += graph_ford_fulkerson(&residual_graph, source, sink, predecessor);
    }

    graph_free(&residual_graph);

    return max_flow;
}
