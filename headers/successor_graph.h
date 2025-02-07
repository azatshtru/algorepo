#include "../headers/graph.h"
#include "../headers/priority_queue.h"
#include "../headers/miniqutils.h"

#ifndef SUCCESSOR_GRAPH
#define SUCCESSOR_GRAPH

int successor_graph_precalculate_succ_i(struct graph* graph, int vertex_i, int limit, int** succ);
void successor_graph_precalculate_succ(struct graph* successor_graph, int limit, int** succ);
struct vertex* successor_graph_succ(struct vertex* v);
int successor_graph_succ_n(struct vertex* v, int k, int** succ);
void successor_graph_floyd_tortoise_and_hair(struct graph* successor_graph, int* first_vertex_index, int* cycle_length);

#endif
