#include "../headers/graph.h"

struct graph graph_new() {
    struct graph graph;
    graph.edges = vec_new(struct edge*);
    graph.vertices = vec_new(struct vertex*);
    graph.freelist = vec_new(int);
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
    vec_push(from->neighbors, to);
    return edge;
}

void graph_remove_edge(struct graph* graph, struct vertex* from, struct vertex* to) {
    struct edge edge_key = { from, to };
    struct edge* edge = hashset_get(graph->edges, &edge_key);
    vec_zap(from->neighbors, vec_index(from->neighbors, to), NULL);
    free(edge);
}

unsigned int graph_vertex_identity(struct graph* graph) {
    if(vec_len(graph->freelist) > 0) {
        return vec_pop(graph->freelist, -1);
    }
    return graph_vertices_len(graph);
}

void graph_add_vertex(struct graph* graph, struct vertex* v) {
    v = malloc(sizeof(struct vertex));
    int identity = graph_vertex_identity(graph);
    v->neighbors = vec_new(struct vertex*);
    v->i = identity;
    if(identity == graph_vertices_len(graph)) {
        vec_push(graph->vertices, v);
    } else {
        vec_set(graph->vertices, identity, v);
    }
}

void graph_remove_vertex(struct graph* graph, struct vertex* v) {
    for(int i = 0; i < vec_len(v->neighbors); i++) {
        struct vertex* to = (*v->neighbors)[i];
        graph_remove_edge(graph, v, to);
    }
    vec_push(graph->freelist, v->i);
    free(v);
}

struct vertex* graph_vertex_by_index(struct graph* graph, int index) {
    return vec_get(graph->vertices, index);
}

struct edge* graph_edge_by_from_to(struct graph* graph, struct vertex* from, struct vertex* to) {
    struct edge edge_key = { from, to };
    return hashset_get(graph->edges, &edge_key);
}

unsigned int graph_vertices_len(struct graph* graph) {
    return vec_len(graph->vertices);
}

unsigned int graph_edges_len(struct graph* graph) {
    return vec_len(graph->edges);
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

struct vertex_int vertex_int_new(int value) {
    struct vertex_int v;
    v.value = value;
    return v;
}

int vertex_int_value(struct vertex* v) {
    return container_from_ptr(struct vertex_int, v, v)->value;
}

struct weighted_edge weighted_edge_new(int weight) {
    struct weighted_edge edge;
    edge.weight = weight;
    return edge;
}

int weighted_edge_weight(struct edge* edge) {
    return container_from_ptr(struct weighted_edge, edge, edge)->weight;
}

