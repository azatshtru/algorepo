#include "graph.h"
#include "queue.h"
#include "miniqutils.h"

#ifndef GRAPH_PATHS_AND_CIRCUITS
#define GRAPH_PATHS_AND_CIRCUITS

int graph_eulerian_path_exists(struct graph* graph, struct vertex** start_vertex);
void graph_hierholzer(struct graph* graph, struct edge** eulerian_path);
void hamiltonian_path_traverse(struct graph* graph, int** previous, int mask, int pos, vector(struct vertex*) path);
int hamiltonian_path(struct graph* graph, struct vertex** path);
int hamiltonian_circuit(struct graph* graph, struct vertex** path);

#endif
