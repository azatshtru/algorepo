#include "graph.h"
#include "acyclic_graph.h"

void graph_kosaraju_dfs(struct graph* graph, void* current, vector(void*) output, int* visited);

int graph_kosaraju(struct graph* graph, void** roots, struct graph* condensed_graph);

struct _2sat {
    vector(long) l_disjunct;
    vector(long) r_disjunct;
};

void _2sat_init(struct _2sat* _2sat);
void _2sat_add_disjunction(struct _2sat* _2sat, long l, long r);
int _2sat_solve(struct _2sat* _2sat, vector(long) output);
void _2sat_free(struct _2sat* _2sat);

