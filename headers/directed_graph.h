#include "../headers/graph.h"
#include "../headers/priority_queue.h"
#include "../headers/miniqutils.h"

#ifndef ACYCLIC_GRAPH
#define ACYCLIC_GRAPH

#define PROCESSING 1
#define PROCESSED 2

int acyclic_graph_topological_sort_reversed(
        struct vertex* v,
        int* state,
        struct vertex** topological_order,
        int topological_order_index
    );

int acyclic_graph_toplogical_sort(struct graph* graph, struct vertex** topological_order);
int acyclic_graph_paths_to(struct graph* graph, struct vertex* s, struct vertex* current, int* paths, int* visited);
int acyclic_graph_paths_between(struct graph* graph, struct vertex* from, struct vertex* to);
void graph_dijkstra_acyclic_product(struct graph* graph, struct vertex* s, struct graph* acyclic_product);

// similar to dijkstra's acyclic product, all dynamic programming problems result in an acyclic graph where
// each node represents a state and the edges represent a path taken from that state

#endif

#ifndef SUCCESSOR_GRAPH
#define SUCCESSOR_GRAPH

int successor_graph_precalculate_succ_i(struct graph* graph, int vertex_i, int limit, int** succ);
void successor_graph_precalculate_succ(struct graph* successor_graph, int limit, int** succ);
struct vertex* successor_graph_succ(struct vertex* v);
int successor_graph_succ_n(struct vertex* v, int k, int** succ);
void successor_graph_floyd_tortoise_and_hair(struct graph* successor_graph, int* first_vertex_index, int* cycle_length);

#endif
