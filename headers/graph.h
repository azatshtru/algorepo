#ifndef GRAPH
#define GRAPH

#include "vector.h"
#include "hashset.h"
#include "miniqutils.h"
#include "queue.h"

struct vertex {
    void* value;
    int i;
    vector(struct vertex*) out;
    vector(struct vertex*) in;
};

struct edge {
    void* from;
    void* to;
    int weight;
};

struct graph {
    vector(void*) vertices;
    hashset(struct vertex*) adjacency_list;
    hashset(struct edge*) edges;
};

unsigned int graph_edge_hash(void* edge_ptr);
int graph_edge_cmp(void* edge1, void* edge2);
unsigned int graph_vertex_hash(void* v_ptr);
int graph_vertex_cmp(void* v1, void* v2);

struct graph graph_new();
void graph_free(struct graph* graph);

void graph_edges(struct graph* graph, struct edge** edges);

struct vertex* graph_vertex(struct graph* graph, void* value);
struct edge* graph_edge_between(struct graph* graph, void* from, void* to);

void graph_add_edge(struct graph* graph, void* from, void* to, int weight);
void graph_add_edge_symmetric(struct graph* graph, void* from, void* to, int weight);
void graph_remove_edge(struct graph* graph, void* from, void* to);
void graph_remove_edge_symmetric(struct graph* graph, void* from, void* to);
void graph_add_vertex(struct graph* graph, void* value);
void graph_remove_vertex(struct graph* graph, void* value);

unsigned int graph_vertices_len(struct graph* graph);
unsigned int graph_edges_len(struct graph* graph);

int graph_vertices_are_adjacent(struct graph* graph, void* x, void* y);

struct vertex* graph_vertex_out(struct graph* graph, void* x, int index);
struct vertex* graph_vertex_in(struct graph* graph, void* x, int index);
int graph_vertex_out_degree(struct graph* graph, void* x);
int graph_vertex_in_degree(struct graph* graph, void* x);

int graph_vertex_i(struct graph* graph, void* x);
void* graph_vertex_from_i(struct graph* graph, int i);

int graph_edge_weight(struct graph* graph, void* from, void* to);
float graph_cmp_edge_by_weight(void* a, void* b);

void graph_as_undirected(struct graph* directed_graph, struct graph* undirected_graph);
int graph_path_exists_between(struct graph* graph, void* a, void* b);
int graph_is_bipartite(struct graph* graph, Color* color);

#endif
