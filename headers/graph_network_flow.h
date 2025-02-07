#include "graph.h"
#include "queue.h"
#include "miniqutils.h"

#ifndef GRAPH_NETWORK_FLOW
#define GRAPH_NETWORK_FLOW

struct ford_fulkerson_flow {
    struct vertex* from;
    struct vertex* to;
    int flow;
    struct ford_fulkerson_flow* reverse;
};

int ford_fulkerson_flow_cmp(void* a, void* b);
unsigned int ford_fulkerson_flow_hash(void* a);
int graph_edmonds_karp_breadth_first_search(
        struct graph* graph,
        struct vertex* source,
        struct vertex* sink,
        struct vertex** predecessor,
        hashset(struct ford_fulkerson_flow) residual
        );

int graph_ford_fulkerson(struct graph* graph, struct vertex* source, struct vertex* sink);
int graph_edmonds_karp(struct graph* graph, struct vertex* source, struct vertex* sink);

#endif
