#ifndef GRAPH
#define GRAPH

#include "vector.h"
#include "hashset.h"
#include "miniqutils.h"

struct vertex {
    void* value;
    int i;
    vector(struct vertex*) out;
    vector(struct vertex*) in;
};

struct edge {
    struct vertex* from;
    struct vertex* to;
    int weight;
};

struct graph {
    vector(struct vertex*) vertices;
    hashset(struct edge*) edges;
};

unsigned int graph_edge_hash(void* edge_ptr);
int graph_edge_cmp(void* edge1, void* edge2);

struct graph* graph_new();
void graph_free(struct graph* graph);

void graph_edges(struct graph* graph, struct edge** edges);

struct edge* graph_edge_between(struct graph* graph, struct vertex* from, struct vertex* to);

void graph_add_edge(struct graph* graph, struct vertex* from, struct vertex* to, int weight);
void graph_remove_edge(struct graph* graph, struct vertex* from, struct vertex* to);
struct vertex* graph_add_vertex(struct graph* graph, void* value);
void graph_remove_vertex(struct graph* graph, struct vertex* value);

unsigned int graph_vertices_len(struct graph* graph);
unsigned int graph_edges_len(struct graph* graph);

int graph_vertices_are_adjacent(struct graph* graph, struct vertex* x, struct vertex* y);

void* graph_vertex_out(struct graph* graph, struct vertex* x, int index);
void* graph_vertex_in(struct graph* graph, struct vertex* x, int index);
int graph_vertex_out_degree(struct vertex* x);
int graph_vertex_in_degree(struct vertex* x);

int graph_vertex_i(struct vertex* x);
struct vertex* graph_vertex_from_i(struct graph* graph, int i);

int graph_edge_weight(struct graph* graph, struct vertex* from, struct vertex* to);
float graph_cmp_edge_by_weight(void* a, void* b);

#endif
