#include "../headers/graph.h"
#include "../headers/priority_queue.h"
#include "../headers/miniqutils.h"

#ifndef ACYCLIC_GRAPH
#define ACYCLIC_GRAPH

#define PROCESSING 1
#define PROCESSED 2

int acyclic_graph_topological_sort_reversed(
        struct graph* graph,
        void* v,
        int* state,
        void** topological_order,
        int topological_order_index);

int acyclic_graph_toplogical_sort(struct graph* graph, void** topological_order);
int acyclic_graph_paths_to(struct graph* graph, void* s, void* current, int* paths, int* visited);
int acyclic_graph_paths_between(struct graph* graph, void* from, void* to);
void graph_dijkstra_acyclic_product(struct graph* graph, void* s, struct graph* acyclic_product);

// similar to dijkstra's acyclic product, all dynamic programming problems result in an acyclic graph where
// each node represents a state and the edges represent a path taken from that state

#endif
