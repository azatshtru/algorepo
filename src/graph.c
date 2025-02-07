#include "../headers/graph.h"
#include "../headers/logging.h"

unsigned int graph_edge_hash(void* edge_ptr) {
    struct edge* edge = *((struct edge**)edge_ptr);
    return cantor_pairing((unsigned long long)edge->from, (unsigned long long)edge->to);
}

int graph_edge_cmp(void* edge1, void* edge2) {
    struct edge* a = *((struct edge**)edge1);
    struct edge* b = *((struct edge**)edge2);
    return a->from == b->from && a->to == b->to;
}

unsigned int graph_vertex_hash(void* v_ptr) {
    struct vertex* v = *((struct vertex**)v_ptr);
    return (unsigned long long)v->value;
}

int graph_vertex_cmp(void* v1, void* v2) {
    struct vertex* a = *((struct vertex**)v1);
    struct vertex* b = *((struct vertex**)v2);
    return a->value == b->value;
}

struct graph graph_new() {
    struct graph graph;
    graph.edges = hashset_new(struct edge*, graph_edge_hash, graph_edge_cmp);
    graph.adjacency_list = hashset_new(struct vertex*, graph_vertex_hash, graph_vertex_cmp);
    graph.vertices = vec_new(void*);
    return graph;
}

void graph_free(struct graph* graph) {
    void** vertices = graph_vertices(graph);
    for(int i = 0; i < graph_vertices_len(graph); i++) {
        struct vertex* v = graph_vertex(graph, vertices[i]);
        graph_remove_vertex(graph, v->value);
    }
    hashset_free(graph->edges, NULL);
    hashset_free(graph->adjacency_list, NULL);
    vec_free(graph->vertices, NULL);
}

void** graph_vertices(struct graph* graph) {
    return vec_as_array(graph->vertices);
}

void graph_edges(struct graph* graph, struct edge** edges) {
    unsigned int i = 0;
    int j = 0;
    do {
        i = hashset_lazy_iterate(graph->edges, i);
        edges[j++] = (*graph->edges)[i];
    } while(i != 0);
}

struct vertex* graph_vertex(struct graph* graph, void* value) {
    struct vertex* v = malloc(sizeof(struct vertex));
    v->value = value;
    return hashset_get(graph->adjacency_list, v);
}

struct edge* graph_edge_between(struct graph* graph, void* from, void* to) {
    struct edge edge_key = { from, to, 0 };
    return hashset_contains(graph->edges, &edge_key) ? hashset_get(graph->edges, &edge_key) : NULL;
}

void graph_add_edge(struct graph* graph, void* from, void* to, int weight) {
    struct edge edge_value = { from, to, weight };
    struct edge* edge = malloc(sizeof(struct edge));
    *edge = edge_value;

    if(hashset_contains(graph->edges, edge)) { return; }
    vec_push(graph_vertex(graph, from)->out, to);
    vec_push(graph_vertex(graph, to)->in, from);
    hashset_insert(graph->edges, edge);
}

void graph_remove_edge(struct graph* graph, void* from, void* to) {
    struct edge* edge = graph_edge_between(graph, from, to);
    if(edge) {
        hashset_remove(graph->edges, edge);
        struct vertex* from_vertex = graph_vertex(graph, from);
        struct vertex* to_vertex = graph_vertex(graph, to);
        vec_zap(from_vertex->out, vec_index(from_vertex->out, to), NULL);
        vec_zap(to_vertex->in, vec_index(to_vertex->in, from), NULL);
        free(edge);
    }
}

void graph_add_vertex(struct graph* graph, void* value) {
    struct vertex* v = malloc(sizeof(struct vertex));
    v->value = value;
    v->i = vec_len(graph->vertices);
    v->in = vec_new(void*);
    v->out = vec_new(void*);
    hashset_insert(graph->adjacency_list, v);
    vec_push(graph->vertices, value);
}

void graph_remove_vertex(struct graph* graph, void* value) {
    struct vertex* v = graph_vertex(graph, value);
    for(int i = vec_len(v->out) - 1; i >= 0; i--) {
        void* u = vec_get(v->out, i);
        graph_remove_edge(graph, value, u);
    }
    for(int i = vec_len(v->in) - 1; i >= 0; i--) {
        void* u = vec_get(v->in, i);
        graph_remove_edge(graph, u, value);
    }
    vec_free(v->out, NULL);
    vec_free(v->in, NULL);

    void* u = graph_vertices(graph)[vec_len(graph->vertices) - 1];
    vec_set(graph->vertices, v->i, u);
    graph_vertex(graph, u)->i = v->i;

    vec_zap(graph->vertices, -1, NULL);

    hashset_remove(graph->adjacency_list, v);
    free(v);
}

unsigned int graph_vertices_len(struct graph* graph) {
    return hashset_len(graph->adjacency_list);
}

unsigned int graph_edges_len(struct graph* graph) {
    return hashset_len(graph->edges);
}

int graph_vertices_are_adjacent(struct graph* graph, void* x, void* y) {
    return graph_edge_between(graph, x, y) || graph_edge_between(graph, y, x);
}

int graph_vertex_out_degree(struct graph* graph, void* x) {
    return vec_len(graph_vertex(graph, x)->out);
}

int graph_vertex_in_degree(struct graph* graph, void* x) {
    return vec_len(graph_vertex(graph, x)->in);
}

void** graph_vertex_out(struct graph* graph, void* x) {
    return vec_as_array(graph_vertex(graph, x)->out);
}

void** graph_vertex_in(struct graph* graph, void* x) {
    return vec_as_array(graph_vertex(graph, x)->in);
}

int graph_edge_weight(struct graph* graph, void* from, void* to) {
    return graph_edge_between(graph, from, to)->weight;
}

float graph_cmp_edge_by_weight(void* a, void* b) {
    return ((struct edge*)a)->weight - ((struct edge*)b)->weight;
}
