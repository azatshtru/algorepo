#ifndef GRAPH
#define GRAPH

#include "vector.h"
#include "hashset.h"
#include "miniqutils.h"

struct vertex {
    vector(struct vertex*) neighbors;
    unsigned int i;
};

struct edge {
    struct vertex* from;
    struct vertex* to;
};

struct graph {
    unsigned int vertex_identity;
    vector(struct vertex*) vertices;
    hashset(struct edge*) edges;
    vector(int) freelist;
};

struct graph graph_new();
void graph_free(struct graph* graph);

unsigned int graph_edge_hash(void* edge_ptr);
int graph_edge_cmp(void* edge1, void* edge2);

struct vertex* graph_add_vertex(struct graph* graph);
void graph_remove_vertex(struct graph* graph, struct vertex* x);
struct edge* graph_add_edge(struct graph* graph, struct vertex* from, struct vertex* to);
void graph_remove_edge(struct graph* graph, struct vertex* from, struct vertex* to);

int graph_vertex_adjacent(struct vertex* x, struct vertex* y);
int graph_vertex_neighbors_len(struct vertex* x);
vector(struct vertex*) graph_vertex_neighbors(struct vertex* x);

#endif
