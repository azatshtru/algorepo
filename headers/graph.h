#ifndef GRAPH
#define GRAPH

#include "vector.h"
#include "hashset.h"
#include "miniqutils.h"

struct vertex {
    hashset(struct vertex*) neighbors;
};

struct edge {
    struct vertex* from;
    struct vertex* to;
};

struct graph {
    vector(struct vertex) vertices;
    vector(struct edge) edges;
};

struct graph graph_new();
void graph_adjacent(struct graph* graph, struct vertex* x, struct vertex* y);
int graph_neighbors_len(struct graph* graph, struct vertex* x);
void graph_neighbors(struct vertex* neighbours, struct graph graph, struct vertex* x);
struct vertex* graph_add_vertex(struct graph graph);
void graph_remove_vertex(struct graph* graph, struct vertex x);
struct edge* graph_add_edge(struct graph* graph, struct vertex* from, struct vertex* to);
void graph_remove_edge(struct graph* graph, struct vertex* from, struct vertex* to);

#endif
