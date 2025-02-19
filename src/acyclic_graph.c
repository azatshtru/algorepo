#include "../headers/acyclic_graph.h"
#include "../headers/logging.h"

int acyclic_graph_topological_sort_reversed(struct graph* graph, void* current, int* state, vector(void*) topological_order) {
    struct vertex* u = graph_vertex(graph, current);
    if(state[u->i] == 1) return 1;
    if(state[u->i] == 2) return 0;
    int is_cyclic = 0;
    state[u->i] = 1;
    for(int i = 0; i < vec_len(u->out); i++) {
        struct vertex* v = vec_get(u->out, i);
        is_cyclic = acyclic_graph_topological_sort_reversed(graph, v->value, state, topological_order);
        if(is_cyclic) return 1;
    }
    state[u->i] = 2;
    if(topological_order != NULL) {
        vec_push(topological_order, current);
    }
    return is_cyclic;
}

int acyclic_graph_toplogical_sort(struct graph* graph, vector(void*) topological_order) {
    int vertex_len = graph_vertices_len(graph);
    int state[vertex_len];
    memzero(state, sizeof(int) * vertex_len);
    for(int i = 0; i < vertex_len; i++) {
        if(state[i] == 2) continue;
        int is_cyclic = acyclic_graph_topological_sort_reversed(graph, vec_get(graph->vertices, i), state, topological_order);
        if(is_cyclic) return 0;
    }
    vec_reverse(topological_order);
    return 1;
}

int acyclic_graph_paths_to(struct graph* graph, void* s, void* current, int* paths, int* visited) {
    struct vertex* current_adj = graph_vertex(graph, current);
    if(visited[current_adj->i]) {
        return paths[current_adj->i];
    }
    visited[current_adj->i] = 1;
    if(current == s) return 1;
    int pathsum = 0;
    for(int i = 0; i < graph_vertex_out_degree(graph, current); i++) {
        void* u = vec_get(current_adj->out, i)->value;
        pathsum += acyclic_graph_paths_to(graph, s, u, paths, visited);
    }
    paths[current_adj->i] = pathsum;
    return pathsum;
}

int acyclic_graph_paths_between(struct graph* graph, void* from, void* to) {
    int vertex_len = graph_vertices_len(graph);
    int paths[vertex_len];
    int visited[vertex_len];
    for(int i = 0; i < vertex_len; i++) { 
        paths[i] = 0;
        visited[i] = 0;
    }
    paths[graph_vertex_i(graph, to)] = 1;

    acyclic_graph_paths_to(graph, to, from, paths, visited);

    return paths[graph_vertex_i(graph, from)];
}

void graph_dijkstra_acyclic_product(struct graph* graph, void* s, struct graph* acyclic_product) {
    int vertex_len = graph_vertices_len(graph);
    int distance[vertex_len];
    int processed[vertex_len];

    PriorityQueue(struct vertex*) q = priority_queue_new(struct vertex*);

    for(int i = 0; i < vertex_len; i++) { 
        distance[i] = I32_MAX;
        processed[i] = 0;
        graph_add_vertex(acyclic_product, graph_vertex_from_i(graph, i));
    }
    distance[graph_vertex_i(graph, s)] = 0;
    priority_queue_nq(q, graph_vertex(graph, s), 0);

    while(!priority_queue_is_empty(q)) {
        struct vertex* v = priority_queue_dq(q);
        if(processed[v->i]) { continue; }
        processed[v->i] = 1;
        for(int i = 0; i < vec_len(v->out); i++) {
            struct vertex* u = vec_get(v->out, i);
            int weight = graph_edge_weight(graph, v->value, u->value);
            if(distance[v->i] + weight < distance[u->i]) {
                distance[u->i] = distance[v->i] + weight;
                priority_queue_nq(q, u, distance[u->i]);

                for(int i = 0; i < vec_len(u->in); i++) {
                    graph_remove_edge(acyclic_product, vec_get(u->in, i), u->value);
                }
            } else if(distance[v->i] + weight > distance[u->i]) continue;
            graph_add_edge(acyclic_product, v->value, u->value, graph_edge_weight(graph, v->value, u->value));
        }
    }

    priority_queue_free(q, NULL);
}

// similar to dijkstra's acyclic product, all dynamic programming problems result in an acyclic graph where
// each node represents a state and the edges represent a path taken from that state
