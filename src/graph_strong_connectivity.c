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
