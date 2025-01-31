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

void de_bruijn_traverse(int* a, int t, int p, int k, int n, vector(int) sequence);
void de_bruijn(int k, int n, vector(char) out);

int knight_move_is_valid(int** board, int n, int x, int y);
int knight_moves_count(int** board, int n, int x, int y);
int knight_move_warnsdorff(int** board, int n, int *x, int *y);
int knights_tour(int** board, int n, int start_x, int start_y);

#endif
