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
    struct graph* graph,
    struct vertex* source,
    struct vertex* sink,
    struct vertex** predecessor,
    hashset(struct ford_fulkerson_flow) residual
) {
    int vertex_len = graph_vertices_len(graph);

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
            struct ford_fulkerson_flow flow = { current, u, 0, NULL };
            if(!visited[u->i] && hashset_get(residual, flow).flow > 0) {
                queue_push_back(q, u);
                predecessor[u->i] = current;
                visited[u->i] = 1;

                if(u == sink) {
                    return 1;
                }
            }
        }
    }
    return 0;
}

int graph_ford_fulkerson(struct graph* graph, struct vertex* source, struct vertex* sink) {

}

int graph_edmonds_karp(struct graph* graph, struct vertex* source, struct vertex* sink) {
    int vertex_len = graph_vertices_len(graph);
    struct vertex* predecessor[vertex_len];

    struct weighted_edge edges[graph_edges_len(graph)];
    struct graph residual_graph = graph_new();
    struct weighted_edge* edge = malloc(sizeof(struct weighted_edge));

    hashset(struct ford_fulkerson_flow) residual = hashset_new(
                struct ford_fulkerson_flow, ford_fulkerson_flow_hash, ford_fulkerson_flow_cmp);

    struct edge* edges[graph_edges_len(graph)];
    graph_edges(graph, edges);
    for(int i = 0; i < graph_edges_len(graph); i++) {
        struct ford_fulkerson_flow flow = { edges[0]->from, edges[1]->to, weighted_edge_weight(edges[0]), NULL };
        struct ford_fulkerson_flow reverse_flow = { edges[0]->to, edges[1]->from, 0, NULL };
        hashset_insert(residual, flow);
    }

    int max_flow = 0;

    while (graph_edmonds_karp_breadth_first_search(graph, source, sink, predecessor, residual)) {
        int path_flow = I32_MAX;

        for (struct vertex* v = sink; v != source; v = predecessor[v->i]) {
            struct vertex* u = predecessor[v->i];
            struct ford_fulkerson_flow flow = { graph_edge_between(graph, u, v), 0 };
            flow = hashset_get(residual, flow);
            path_flow = path_flow < flow.flow ? path_flow : flow.flow;
        }

        for (struct vertex* v = sink; v != source; v = predecessor[v->i]) {
            struct vertex* u = predecessor[v->i];
            struct ford_fulkerson_flow flow = { graph_edge_between(graph, u, v), 0 };
            flow = hashset_get(residual, flow);
            hashset_insert(residual, )
            residualGraph[u][v] -= pathFlow;
            residualGraph[v][u] += pathFlow;  // Reverse flow to allow backtracking if needed
        }

        maxFlow += pathFlow;
    }

    return maxFlow;

    hashset_free(residual, NULL);
}
