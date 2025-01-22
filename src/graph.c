#include "../headers/graph.h"

struct graph graph_new() {
    struct graph graph;
    graph.edges = hashset_new(struct edge*, graph_edge_hash, graph_edge_cmp);
    graph.vertices = vec_new(struct vertex*);
    graph.freelist = vec_new(int);
    return graph;
}

void graph_free(struct graph* graph) {
    for(int i = 0; i < vec_len(graph->vertices); i++) {
        if(vec_contains(graph->freelist, i)) { continue; }
        struct vertex* v = graph_vertex_from_id(graph, i);
        graph_remove_vertex(graph, v);
    }
    hashset_free(graph->edges, NULL);
    vec_free(graph->vertices, NULL);
    vec_free(graph->freelist, NULL);
}

unsigned int graph_edge_hash(void* edge_ptr) {
    struct edge* edge = *((struct edge**)edge_ptr);
    return cantor_pairing(edge->from->i, edge->to->i);
}

int graph_edge_cmp(void* edge1, void* edge2) {
    struct edge* a = *((struct edge**)edge1);
    struct edge* b = *((struct edge**)edge2);
    return a->from->i == b->from->i && a->to->i == b->to->i;
}

void print_vertex_neighbor_i(struct vertex* v) {
    printf("%d\n", v->i);
}

struct edge* graph_add_edge(struct graph* graph, struct vertex* from, struct vertex* to) {
    struct edge* edge = malloc(sizeof(struct edge));
    edge->from = from;
    edge->to = to;
    vec_push(from->out, to);
    vec_push(to->in, from);
    hashset_insert(graph->edges, edge);
    return edge;
}

void graph_remove_edge(struct graph* graph, struct vertex* from, struct vertex* to) {
    struct edge* edge = graph_edge_between(graph, from, to);
    if(edge != NULL) {
        hashset_remove(graph->edges, edge);
        vec_zap(from->out, vec_index(from->out, to), NULL);
        vec_zap(to->in, vec_index(to->in, from), NULL);
        free(edge);
    }
}

unsigned int graph_vertex_identity(struct graph* graph) {
    if(vec_len(graph->freelist) > 0) {
        return vec_pop(graph->freelist, -1);
    }
    return graph_vertices_len(graph);
}

struct vertex* graph_add_vertex(struct graph* graph) {
    struct vertex* v = malloc(sizeof(struct vertex));
    int identity = graph_vertex_identity(graph);
    v->in = vec_new(struct vertex*);
    v->out = vec_new(struct vertex*);
    v->i = identity;
    if(identity == graph_vertices_len(graph)) {
        vec_push(graph->vertices, v);
    } else {
        vec_set(graph->vertices, identity, v);
    }
    return v;
}

void graph_remove_vertex(struct graph* graph, struct vertex* v) {
    if(vec_contains(graph->freelist, v->i)) { return; }
    for(int i = vec_len(v->out) - 1; i >= 0; i--) {
        struct vertex* u = vec_get(v->out, i);
        graph_remove_edge(graph, v, u);
    }
    for(int i = vec_len(v->in) - 1; i >= 0; i--) {
        struct vertex* u = vec_get(v->in, i);
        graph_remove_edge(graph, u, v);
    }
    vec_push(graph->freelist, v->i);
    vec_free(v->out, NULL);
    vec_free(v->in, NULL);
    free(v);
}

struct vertex* graph_vertex_from_id(struct graph* graph, int index) {
    return vec_get(graph->vertices, index);
}

struct edge* graph_edge_between(struct graph* graph, struct vertex* from, struct vertex* to) {
    struct edge edge_key = { from, to };
    return hashset_contains(graph->edges, &edge_key) ? hashset_get(graph->edges, &edge_key) : NULL;
}

unsigned int graph_vertices_len(struct graph* graph) {
    return vec_len(graph->vertices) - vec_len(graph->freelist);
}

unsigned int graph_edges_len(struct graph* graph) {
    return hashset_len(graph->edges);
}

int graph_vertex_adjacent(struct graph* graph, struct vertex* x, struct vertex* y) {
    return graph_edge_between(graph, x, y) || graph_edge_between(graph, y, x);
}

int graph_vertex_out_degree(struct vertex* x) {
    return vec_len(x->out);
}

int graph_vertex_in_degree(struct vertex* x) {
    return vec_len(x->in);
}

struct vertex_int vertex_int_init(struct graph* graph, int value) {
    struct vertex_int v;
    v.value = value;
    v.v = graph_add_vertex(graph);
    return v;
}

int vertex_int_value(struct vertex* v) {
    return container_from_ptr(struct vertex_int, v, v)->value;
}

struct weighted_edge weighted_edge_init(struct graph* graph, int weight, struct vertex* from, struct vertex* to) {
    struct weighted_edge edge;
    edge.weight = weight;
    graph_add_edge(graph, from, to);
    return edge;
}

int weighted_edge_weight(struct edge* edge) {
    return container_from_ptr(struct weighted_edge, edge, edge)->weight;
}

