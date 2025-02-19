#include "graph.h"

void graph_kosaraju_dfs(struct graph* graph, void* current, vector(void*) output, int* visited);

int graph_kosaraju(struct graph* graph, void** roots, struct graph* condensed_graph);
