#include "graph.h"
#include "queue.h"
#include "miniqutils.h"

#ifndef GRAPH_NETWORK_FLOW
#define GRAPH_NETWORK_FLOW

int graph_edmonds_karp_breadth_first_search(
        struct graph* residual_graph,
        struct vertex* source,
        struct vertex* sink,
        struct vertex** predecessor
        );

void graph_network_flow_init_residual_graph(struct graph* graph, struct graph* residual_graph);
int graph_ford_fulkerson(struct graph* residual_graph, struct vertex* source, struct vertex* sink, struct vertex** predecessor);
int graph_edmonds_karp(struct graph* graph, struct vertex* source, struct vertex* sink);
int graph_max_flow(struct graph* graph, struct vertex* source, struct vertex* sink);
int graph_min_cut(struct graph* graph, struct vertex* source, struct vertex* sink, vector(struct edge*) min_cut);

int graph_max_node_disjoint_paths(struct graph* graph, struct vertex* source, struct vertex* sink);

#endif
