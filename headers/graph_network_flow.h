#include "graph.h"
#include "queue.h"
#include "miniqutils.h"

#ifndef GRAPH_NETWORK_FLOW
#define GRAPH_NETWORK_FLOW

int graph_edmonds_karp_breadth_first_search(
        struct graph* residual_graph,
        void* source,
        void* sink,
        struct vertex** predecessor
        );

int graph_ford_fulkerson(struct graph* residual_graph, void* source, void* sink, struct vertex** predecessor);
int graph_edmonds_karp(struct graph* graph, void* source, void* sink);

#endif
