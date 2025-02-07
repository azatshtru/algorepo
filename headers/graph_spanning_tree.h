#include "graph.h"
#include "sorting.h"
#include "disjoint_set_int.h"
#include "priority_queue.h"
#include "miniqutils.h"

#ifndef GRAPH_SPANNING_TREE
#define GRAPH_SPANNING_TREE

void graph_kruskal(struct graph* graph, struct graph* spanning_tree);
void graph_prim(struct graph* graph, struct graph* spanning_tree);

#endif

