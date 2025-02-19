#include "../headers/graph_strong_connectivity.h"
#include "../headers/logging.h"

void graph_kosaraju_dfs(struct graph* graph, void* current, vector(void*) output, int* visited) {
    struct vertex* v = graph_vertex(graph, current);
    visited[v->i] = 1;
    for(int i = 0; i < vec_len(v->out); i++) {
        struct vertex* u = vec_get(v->out, i);
        if (!visited[u->i])
            graph_kosaraju_dfs(graph, u->value, output, visited);
    }
    vec_push(output, v->value);
}

int graph_kosaraju(struct graph* graph, void** roots, struct graph* condensed_graph) {
    unsigned int vertex_len = graph_vertices_len(graph);
    int visited[vertex_len];
    memzero(visited, sizeof(int) * vertex_len);

    vector(void*) order = vec_new(void*);

    for (int i = 0; i < vertex_len; i++) {
        if (!visited[i]) {
            graph_kosaraju_dfs(graph, vec_get(graph->vertices, i), order, visited);
        }
    }

    struct graph transpose = graph_new();
    for (int j = 0; j < vertex_len; j++) {
        graph_add_vertex(&transpose, vec_get(graph->vertices, j));
    }
    for (int j = 0; j < vertex_len; j++) {
        struct vertex* v = graph_vertex(graph, vec_get(graph->vertices, j));
        for(int i = 0; i < vec_len(v->out); i++) {
            struct vertex* u = vec_get(v->out, i);
            graph_add_edge(&transpose, u->value, v->value, 1);
        }
    }

    memzero(visited, sizeof(int) * vertex_len);
    vec_reverse(order);

    for(int i = 0; i < vec_len(order); i++) {
        struct vertex* v = graph_vertex(graph, vec_get(order, i));
        if (!visited[v->i]) {
            vector(void*) component = vec_new(void*);
            graph_kosaraju_dfs(&transpose, v->value, component, visited);
            void* root = v->value;
            graph_add_vertex(condensed_graph, root);
            for(int j = 0; j < vec_len(component); j++) {
                struct vertex* u = graph_vertex(graph, vec_get(component, j));
                roots[u->i] = root;
            }
        }
    }

    for (int j = 0; j < vertex_len; j++) {
        struct vertex* v = graph_vertex(graph, vec_get(graph->vertices, j));
        for(int i = 0; i < vec_len(v->out); i++) {
            struct vertex* u = vec_get(v->out, i);
            if (roots[v->i] != roots[u->i]) {
                graph_add_edge(condensed_graph, roots[v->i], roots[u->i], 1);
            }
        }
    }

    return graph_vertices_len(condensed_graph);
}

void _2sat_init(struct _2sat* _2sat) {
    _2sat->l_disjunct = vec_new(long);
    _2sat->r_disjunct = vec_new(long);
}

void _2sat_add_disjunction(struct _2sat* _2sat, long l, long r) {
    vec_push(_2sat->l_disjunct, l);
    vec_push(_2sat->r_disjunct, r);
}

int _2sat_long_cmp(void* a, void* b) {
    return *(long*)a == *(long*)b;
}

unsigned int _2sat_long_hash(void* a) {
    return (53 * *(long*)a + 37) % 60493;
}

int _2sat_solve(struct _2sat* _2sat, vector(long) output) {
    struct graph graph = graph_new();
    vector(int) unique = vec_new(int);
    for(int i = 0; i < vec_len(_2sat->l_disjunct); i++) {
        if(!graph_vertex(&graph, (void*)vec_get(_2sat->l_disjunct, i))) {
            graph_add_vertex(&graph, (void*)vec_get(_2sat->l_disjunct, i));
            graph_add_vertex(&graph, (void*)(-vec_get(_2sat->l_disjunct, i)));
        }
    }
    for(int i = 0; i < vec_len(_2sat->r_disjunct); i++) {
        if(!graph_vertex(&graph, (void*)vec_get(_2sat->r_disjunct, i))) {
            graph_add_vertex(&graph, (void*)vec_get(_2sat->r_disjunct, i));
            graph_add_vertex(&graph, (void*)(-vec_get(_2sat->r_disjunct, i)));
        }
    }

    for(int i = 0; i < vec_len(_2sat->l_disjunct); i++) {
        long l = vec_get(_2sat->l_disjunct, i);
        long r = vec_get(_2sat->r_disjunct, i);
        graph_add_edge(&graph, (void*)(-l), (void*)r, 1);
        graph_add_edge(&graph, (void*)(-r), (void*)l, 1);
    }

    struct graph condensed_graph = graph_new();
    void* roots[graph_vertices_len(&graph)];
    int components_len = graph_kosaraju(&graph, roots, &condensed_graph);

    vector(void*) components[components_len];
    for(int i = 0; i < components_len; i++) {
        components[i] = vec_new(void*);
    }

    for(int i = 0; i < graph_vertices_len(&graph); i++) {
        int index = graph_vertex_i(&condensed_graph, roots[i]);
        vec_push(components[index], vec_get(graph.vertices, i));
    }

    for(int i = 0; i < components_len; i++) {
        hashset(long) contains = hashset_new(long, _2sat_long_hash, _2sat_long_cmp);
        for(int j = 0; j < vec_len(components[i]); j++) {
            if(hashset_contains(contains, -(long)vec_get(components[i], j))) return 0;
            hashset_insert(contains, (long)vec_get(components[i], j));
        }
        hashset_free(contains, NULL);
    }

    vector(void*) order = vec_new(void*);
    acyclic_graph_toplogical_sort(&condensed_graph, order);
    vec_reverse(order);

    hashset(long) processed = hashset_new(long, _2sat_long_hash, _2sat_long_cmp);

    for(int i = 0; i < vec_len(order)/2; i++) {
        int index = graph_vertex(&condensed_graph, vec_get(order, i))->i;
        for(int j = 0; j < vec_len(components[index]); j++) {
            long x = (long)vec_get(components[index], j);
            if(hashset_contains(processed, x)) continue;
            hashset_insert(processed, x);
            vec_push(output, x);
        }
    }

    hashset_free(processed, NULL);
    vec_free(unique, NULL);
    graph_free(&graph);
    graph_free(&condensed_graph);
    
    return 1;
}

void _2sat_free(struct _2sat* _2sat) {
    vec_free(_2sat->l_disjunct, NULL);
    vec_free(_2sat->r_disjunct, NULL);
}
