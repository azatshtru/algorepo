#include "graph.h"
#include "queue.h"
#include "miniqutils.h"

#ifndef GRAPH_PATHS_AND_CIRCUITS
#define GRAPH_PATHS_AND_CIRCUITS

int graph_eulerian_path_exists(struct graph* graph, struct vertex** start_vertex);
void graph_hierholzer(struct graph* graph, struct edge** eulerian_path);

#endif
