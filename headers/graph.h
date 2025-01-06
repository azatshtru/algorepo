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
    vector(struct vertex*) vertices;
    hashset(struct edge*) edges;
    vector(int) freelist;
};

struct graph graph_new();
void graph_free(struct graph* graph);

unsigned int graph_edge_hash(void* edge_ptr);
int graph_edge_cmp(void* edge1, void* edge2);

unsigned int graph_vertices_len(struct graph* graph);
unsigned int graph_edges_len(struct graph* graph);

void graph_add_vertex(struct graph* graph, struct vertex* v);
void graph_remove_vertex(struct graph* graph, struct vertex* x);
struct edge* graph_add_edge(struct graph* graph, struct vertex* from, struct vertex* to);
void graph_remove_edge(struct graph* graph, struct vertex* from, struct vertex* to);

struct vertex* graph_vertex_by_index(struct graph* graph, int index);
struct edge* graph_edge_by_from_to(struct graph* graph, struct vertex* from, struct vertex* to);

int graph_vertex_adjacent(struct vertex* x, struct vertex* y);
int graph_vertex_neighbors_len(struct vertex* x);
vector(struct vertex*) graph_vertex_neighbors(struct vertex* x);

struct vertex_int {
    int value;
    struct vertex v;
};

struct vertex_int vertex_int_new(int value);
int vertex_int_value(struct vertex* v);

struct weighted_edge {
    int weight;
    struct edge edge;
};

struct weighted_edge weighted_edge_new(int weight);
int weighted_edge_weight(struct edge* edge);



#endif
