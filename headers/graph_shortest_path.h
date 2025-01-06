#include "graph.h"
#include "priority_queue.h"

#ifndef GRAPH_SHORTEST_PATH
#define GRAPH_SHORTEST_PATH

unsigned int graph_dijkstra(struct graph* graph, unsigned int s, unsigned int e);
unsigned int graph_bellman_ford(struct graph* graph, unsigned int s, unsigned int e);
unsigned int graph_spfa(struct graph* graph, int s, int e);

#endif
