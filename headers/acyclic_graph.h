#include "../headers/graph.h"
#include "../headers/priority_queue.h"
#include "../headers/miniqutils.h"

#ifndef ACYCLIC_GRAPH
#define ACYCLIC_GRAPH

int acyclic_graph_topological_sort_reversed(
        struct graph* graph,
        void* v,
        int* state,
        vector(void*) topological_order
        );

int acyclic_graph_toplogical_sort(struct graph* graph, vector(void*) topological_order);
int acyclic_graph_paths_to(struct graph* graph, void* s, void* current, int* paths, int* visited);
int acyclic_graph_paths_between(struct graph* graph, void* from, void* to);
void graph_dijkstra_acyclic_product(struct graph* graph, void* s, struct graph* acyclic_product);

// similar to dijkstra's acyclic product, all dynamic programming problems result in an acyclic graph where
// each node represents a state and the edges represent a path taken from that state

#endif
