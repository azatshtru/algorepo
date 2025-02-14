#include "../headers/graph.h"
#include "../headers/logging.h"

unsigned int graph_edge_hash(void* edge_ptr) {
    struct edge* edge = *((struct edge**)edge_ptr);
    return cantor_pairing((unsigned long long)(edge->from), (unsigned long long)(edge->to));
}

int graph_edge_cmp(void* edge1, void* edge2) {
    struct edge* a = *((struct edge**)edge1);
    struct edge* b = *((struct edge**)edge2);
    return a->from == b->from && a->to == b->to;
}

struct graph* graph_new() {
    struct graph* graph = malloc(sizeof(struct graph));
    graph->edges = hashset_new(struct edge*, graph_edge_hash, graph_edge_cmp);
    graph->vertices = vec_new(struct vertex*);
    return graph;
}

void graph_free(struct graph* graph) {
    while(graph_vertices_len(graph) > 0) {
        graph_remove_vertex(graph, vec_get(graph->vertices, 0));
    }
    hashset_free(graph->edges, NULL);
    vec_free(graph->vertices, NULL);
    free(graph);
}

void graph_edges(struct graph* graph, struct edge** edges) {
    unsigned int i = 0;
    int j = 0;
    do {
        i = hashset_lazy_iterate(graph->edges, i);
        edges[j++] = (*graph->edges)[i];
    } while(i != 0);
}

struct edge* graph_edge_between(struct graph* graph, struct vertex* from, struct vertex* to) {
    struct edge edge_key = { from, to, 0 };
    return hashset_contains(graph->edges, &edge_key) ? hashset_get(graph->edges, &edge_key) : NULL;
}

void graph_add_edge(struct graph* graph, struct vertex* from, struct vertex* to, int weight) {
    struct edge edge_value = { from, to, weight };

    if(hashset_contains(graph->edges, &edge_value)) {
        return;
    }

    struct edge* edge = malloc(sizeof(struct edge));
    *edge = edge_value;

    vec_push(from->out, to);
    vec_push(to->in, from);
    hashset_insert(graph->edges, edge);
}

void graph_remove_edge(struct graph* graph, struct vertex* from, struct vertex* to) {
    struct edge* edge = graph_edge_between(graph, from, to);
    if(edge) {
        hashset_remove(graph->edges, edge);
        vec_zap(from->out, vec_index(from->out, to), NULL);
        vec_zap(to->in, vec_index(to->in, from), NULL);
        free(edge);
    }
}

struct vertex* graph_add_vertex(struct graph* graph, void* value) {
    struct vertex* v = malloc(sizeof(struct vertex));
    v->value = value;
    v->i = vec_len(graph->vertices);
    v->in = vec_new(struct vertex*);
    v->out = vec_new(struct vertex*);
    vec_push(graph->vertices, v);
    return v;
}

void graph_remove_vertex(struct graph* graph, struct vertex* v) {
    for(int i = vec_len(v->out) - 1; i >= 0; i--) {
        struct vertex* u = vec_get(v->out, i);
        graph_remove_edge(graph, v, u);
    }
    for(int i = vec_len(v->in) - 1; i >= 0; i--) {
        struct vertex* u = vec_get(v->in, i);
        graph_remove_edge(graph, u, v);
    }
    vec_free(v->out, NULL);
    vec_free(v->in, NULL);

    struct vertex* u = vec_get(graph->vertices, vec_len(graph->vertices) - 1);
    vec_set(graph->vertices, v->i, u);
    u->i = v->i;

    vec_zap(graph->vertices, -1, NULL);
    free(v);
}

unsigned int graph_vertices_len(struct graph* graph) {
    return vec_len(graph->vertices);
}

unsigned int graph_edges_len(struct graph* graph) {
    return hashset_len(graph->edges);
}

int graph_vertices_are_adjacent(struct graph* graph, struct vertex* x, struct vertex* y) {
    return graph_edge_between(graph, x, y) || graph_edge_between(graph, y, x);
}

int graph_vertex_out_degree(struct vertex* x) {
    return vec_len(x->out);
}

int graph_vertex_in_degree(struct vertex* x) {
    return vec_len(x->in);
}

void* graph_vertex_out(struct graph* graph, struct vertex* x, int index) {
    return vec_as_array(x->out)[index];
}

void* graph_vertex_in(struct graph* graph, struct vertex* x, int index) {
    return vec_as_array(x->in)[index];
}

int graph_vertex_i(struct vertex* x) {
    return x->i;
}

struct vertex* graph_vertex_from_i(struct graph* graph, int i) {
    return vec_get(graph->vertices, i);
}

int graph_edge_weight(struct graph* graph, struct vertex* from, struct vertex* to) {
    return graph_edge_between(graph, from, to)->weight;
}

float graph_cmp_edge_by_weight(void* a, void* b) {
    return (*((struct edge**)a))->weight - (*((struct edge**)b))->weight;
}
