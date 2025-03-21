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

unsigned int graph_vertex_hash(void* v_ptr) {
    struct vertex* v = *((struct vertex**)v_ptr);
    return (unsigned long long)(v->value);
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
    while(graph_vertices_len(graph) > 0) {
        graph_remove_vertex(graph, vec_get(graph->vertices, 0));
    }
    hashset_free(graph->edges, NULL);
    hashset_free(graph->adjacency_list, NULL);
    vec_free(graph->vertices, NULL);
}

void graph_edges(struct graph* graph, struct edge** edges) {
    unsigned int i = 0;
    unsigned int j = 0;
    do {
        i = hashset_lazy_iterate(graph->edges, i);
        edges[j++] = (*graph->edges)[i];
    } while(j < graph_edges_len(graph));
}

struct vertex* graph_vertex(struct graph* graph, void* value) {
    struct vertex v = { value, 0, NULL, NULL };
    return hashset_get(graph->adjacency_list, &v);
}

struct edge* graph_edge_between(struct graph* graph, void* from, void* to) {
    struct edge edge_key = { from, to, 0 };
    return hashset_contains(graph->edges, &edge_key) ? hashset_get(graph->edges, &edge_key) : NULL;
}

void graph_add_edge(struct graph* graph, void* from, void* to, int weight) {
    struct edge edge_value = { from, to, weight };

    if(hashset_contains(graph->edges, &edge_value)) {
        struct edge* edge = hashset_get(graph->edges, &edge_value);
        edge->weight = weight;
        return;
    }

    struct edge* edge = malloc(sizeof(struct edge));
    *edge = edge_value;

    vec_push(graph_vertex(graph, from)->out, graph_vertex(graph, to));
    vec_push(graph_vertex(graph, to)->in, graph_vertex(graph, from));
    hashset_insert(graph->edges, edge);
}

void graph_add_edge_symmetric(struct graph* graph, void* from, void* to, int weight) {
    graph_add_edge(graph, from, to, weight);
    graph_add_edge(graph, to, from, weight);
}

void graph_remove_edge(struct graph* graph, void* from, void* to) {
    struct edge* edge = graph_edge_between(graph, from, to);
    if(edge) {
        hashset_remove(graph->edges, edge);
        struct vertex* from_vertex = graph_vertex(graph, from);
        struct vertex* to_vertex = graph_vertex(graph, to);
        vec_zap(from_vertex->out, vec_index(from_vertex->out, to_vertex), NULL);
        vec_zap(to_vertex->in, vec_index(to_vertex->in, from_vertex), NULL);
        free(edge);
    }
}

void graph_remove_edge_symmetric(struct graph* graph, void* from, void* to) {
    graph_remove_edge(graph, from, to);
    graph_remove_edge(graph, to, from);
}

void graph_add_vertex(struct graph* graph, void* value) {
    struct vertex x = { value, 0, NULL, NULL };
    if(hashset_contains(graph->adjacency_list, &x)) return;
    struct vertex* v = malloc(sizeof(struct vertex));
    v->value = value;
    v->i = vec_len(graph->vertices);
    v->in = vec_new(struct vertex*);
    v->out = vec_new(struct vertex*);
    hashset_insert(graph->adjacency_list, v);
    vec_push(graph->vertices, value);
}

void graph_remove_vertex(struct graph* graph, void* value) {
    struct vertex* v = graph_vertex(graph, value);
    for(int i = vec_len(v->out) - 1; i >= 0; i--) {
        struct vertex* u = vec_get(v->out, i);
        graph_remove_edge(graph, value, u->value);
    }
    for(int i = vec_len(v->in) - 1; i >= 0; i--) {
        struct vertex* u = vec_get(v->in, i);
        graph_remove_edge(graph, u->value, value);
    }
    vec_free(v->out, NULL);
    vec_free(v->in, NULL);

    void* u = vec_get(graph->vertices, vec_len(graph->vertices) - 1);
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

struct vertex* graph_vertex_out(struct graph* graph, void* x, int index) {
    return vec_as_array(graph_vertex(graph, x)->out)[index];
}

struct vertex* graph_vertex_in(struct graph* graph, void* x, int index) {
    return vec_as_array(graph_vertex(graph, x)->in)[index];
}

int graph_vertex_i(struct graph* graph, void* x) {
    return graph_vertex(graph, x)->i;
}

void* graph_vertex_from_i(struct graph* graph, int i) {
    return vec_get(graph->vertices, i);
}

int graph_edge_weight(struct graph* graph, void* from, void* to) {
    return graph_edge_between(graph, from, to)->weight;
}

float graph_cmp_edge_by_weight(void* a, void* b) {
    return (*((struct edge**)a))->weight - (*((struct edge**)b))->weight;
}

void graph_as_undirected(struct graph* directed_graph, struct graph* undirected_graph) {
    unsigned int vertex_len = graph_vertices_len(directed_graph);
    for(int i = 0; i < vertex_len; i++) {
        graph_add_vertex(undirected_graph, vec_get(directed_graph->vertices, i));
    }
    struct edge* edges[graph_edges_len(directed_graph)];
    graph_edges(directed_graph, edges);
    for(int i = 0; i < graph_edges_len(directed_graph); i++) {
        graph_add_edge_symmetric(undirected_graph, edges[i]->from, edges[i]->to, edges[i]->weight);
    }
}

int graph_path_exists_between(struct graph* graph, void* a, void* b) {
    VecDeque(struct vertex*) q = queue_new(struct vertex*);
    int visited[graph_vertices_len(graph)];
    memzero(visited, sizeof(int) * graph_vertices_len(graph));

    queue_push_back(q, graph_vertex(graph, a));
    
    while(!queue_is_empty(q)) {
        struct vertex* u = queue_pop_front(q); 
        visited[u->i] = 1;
        if(u->value == b) return 1;
        for(int i = 0; i < vec_len(u->out); i++) {
            struct vertex* v = vec_get(u->out, i);
            if(!visited[v->i]) {
                queue_push_back(q, v);
            }
        }
    }
    return 0;
}

int graph_is_bipartite(struct graph* graph, Color* color) {
    unsigned int vertex_len = graph_vertices_len(graph);
    struct graph undirected_graph = graph_new();
    graph_as_undirected(graph, &undirected_graph);

    if(color == NULL) {
        color = malloc(vertex_len * sizeof(Color));
    }
    memzero(color, sizeof(int) * vertex_len);

    VecDeque(struct vertex*) q = queue_new(struct vertex*);

    for(int i = 0; i < vertex_len; i++) {
        if(color[i]) continue;
      
        color[i] = RED;
        queue_push_back(q, graph_vertex(&undirected_graph, vec_get(undirected_graph.vertices, i)));

        while(!queue_is_empty(q)) {
            struct vertex* u = queue_pop_front(q);
            for(int j = 0; j < vec_len(u->out); j++) {
                struct vertex* v = vec_get(u->out, j);
                if(color[v->i] == 0) {
                    color[v->i] = color[u->i] == RED ? BLUE : RED;
                    queue_push_back(q, v);
                } else if (color[v->i] == color[u->i]) {
                    graph_free(&undirected_graph);
                    queue_free(q, NULL);
                    return 0;
                }
            }
        }
    }
    graph_free(&undirected_graph);
    queue_free(q, NULL);
    return 1;
}
