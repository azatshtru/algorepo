#include "../headers/graph.h"

struct graph graph_new() {
    struct graph graph;
    graph.edges = vec_new(struct edge*);
    graph.vertices = vec_new(struct vertex*);
    graph.freelist = vec_new(int);
    graph.vertex_identity = 0;
    return graph;
}

void graph_free(struct graph* graph) {
    for(int i = 0; i < vec_len(graph->edges); i++) {
        graph_remove_edge(graph, (*graph->edges)[i]->from, (*graph->edges)[i]->to);
    }
    for(int i = 0; i < vec_len(graph->vertices); i++) {
        graph_remove_vertex(graph, (*graph->vertices)[i]);
    }
    vec_free(graph->vertices, NULL);
    vec_free(graph->edges, NULL);
}

unsigned int graph_edge_hash(void* edge_ptr) {
    struct edge* edge = (struct edge*)edge_ptr;
    return cantor_pairing(edge->from->i, edge->to->i);
}

int graph_edge_cmp(void* edge1, void* edge2) {
    struct edge* a = (struct edge*)edge1;
    struct edge* b = (struct edge*)edge2;
    return a->from->i == b->from->i && a->to->i == b->to->i;
}

struct edge* graph_add_edge(struct graph* graph, struct vertex* from, struct vertex* to) {
    struct edge* edge = malloc(sizeof(struct edge));
    edge->from = from;
    edge->to = to;
    hashset_insert(graph->edges, edge);
    return edge;
}

void graph_remove_edge(struct graph* graph, struct vertex* from, struct vertex* to) {
    struct edge edge_key = { from, to };
    struct edge* edge = hashset_get(graph->edges, &edge_key);
    free(edge);
}

unsigned int graph_vertex_identity(struct graph* graph) {
    if(vec_len(graph->freelist) > 0) {
        return vec_pop(graph->freelist, -1);
    }
    return graph->vertex_identity++;
}

struct vertex* graph_add_vertex(struct graph* graph) {
    struct vertex* v = malloc(sizeof(struct vertex));
    v->neighbors = vec_new(struct vertex*);
    v->i = graph_vertex_identity(graph);
    return v;
}

void graph_remove_vertex(struct graph* graph, struct vertex* v) {
    for(int i = 0; i < vec_len(v->neighbors); i++) {
        struct vertex* to = (*v->neighbors)[i];
        graph_remove_edge(graph, v, to);
    }
    free(v);
}

int graph_vertex_adjacent(struct vertex* x, struct vertex* y) {
    return vec_contains(x->neighbors, y);
}

int graph_vertex_neighbors_len(struct vertex* x) {
    return vec_len(x->neighbors);
}

vector(struct vertex*) graph_vertex_neighbors(struct vertex* x) {
    return x->neighbors;
}
