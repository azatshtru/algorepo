#include "../headers/acyclic_graph.h"

int acyclic_graph_topological_sort_reversed(struct vertex* v, int* state, struct vertex** topological_order, int topological_order_index) {
    if(state[v->i] == PROCESSED) { return 1; }
    if(state[v->i] == PROCESSING) { return 0; }
    int is_acyclic;
    state[v->i] = PROCESSING;
    for(int i = 0; i < graph_vertex_out_degree(v); i++) {
        struct vertex* u = vec_get(v->out, i);
        is_acyclic = acyclic_graph_topological_sort_reversed(u, state, topological_order, topological_order_index);
        if(is_acyclic == 0) { break; }
    }
    state[v->i] = PROCESSED;
    if(topological_order != NULL) {
        topological_order[topological_order_index++] = v;
    }
    return is_acyclic;
}

int acyclic_graph_toplogical_sort(struct graph* graph, struct vertex** topological_order) {
    int vertex_len = graph_vertices_len(graph);
    int state[vertex_len];
    for(int i = 0; i < vertex_len; i++) {
        state[i] = 0;
    }
    for(int i = 0; i < vertex_len; i++) {
        if(state[i] != 0) { continue; }
        if(acyclic_graph_topological_sort_reversed(graph_vertex_from_i(graph, i), state, topological_order, 0)) {
            continue;
        } else {
            return 1;
        }
    }
    for(int i = 0, j = vertex_len - 1; i < j; i++, j--) {
        swap(topological_order + i, topological_order + j, sizeof(struct vertex*));
    }
    return 0;
}

int acyclic_graph_paths_to(struct graph* graph, struct vertex* s, struct vertex* current, int* paths, int* visited) {
    if(visited[current->i]) {
        return paths[current->i];
    }
    visited[current->i] = 1;
    if(current == s) {
        return 1;
    }
    int pathsum = 0;
    for(int i = 0; i < graph_vertex_out_degree(current); i++) {
        struct vertex* u = vec_get(current->out, i);
        pathsum += acyclic_graph_paths_to(graph, s, u, paths, visited);
    }
    paths[current->i] = pathsum;
    return pathsum;
}

int acyclic_graph_paths_between(struct graph* graph, struct vertex* from, struct vertex* to) {
    int vertex_len = graph_vertices_len(graph);
    int paths[vertex_len];
    int visited[vertex_len];
    for(int i = 0; i < vertex_len; i++) { 
        paths[i] = 0;
        visited[i] = 0;
    }
    paths[to->i] = 1;

    acyclic_graph_paths_to(graph, to, from, paths, visited);

    return paths[from->i];
}

void graph_dijkstra_acyclic_product(struct graph* graph, struct vertex* s, struct graph* acyclic_product) {
    int vertex_len = graph_vertices_len(graph);
    int distance[vertex_len];
    int processed[vertex_len];

    PriorityQueue(struct vertex*) q = priority_queue_new(struct vertex*);

    for(int i = 0; i < vertex_len; i++) { 
        distance[i] = I32_MAX;
        processed[i] = 0;
        graph_add_vertex(acyclic_product, graph_vertex_from_i(graph, i));
    }
    distance[s->i] = 0;
    priority_queue_nq(q, s, 0);

    while(!priority_queue_is_empty(q)) {
        struct vertex* v = priority_queue_dq(q);
        if(processed[v->i]) { continue; }
        processed[v->i] = 1;
        for(int i = 0; i < graph_vertex_out_degree(v); i++) {
            struct vertex* u = vec_get(v->out, i);
            int weight = weighted_edge_weight(graph_edge_between(graph, v, u));
            if(distance[v->i] + weight < distance[u->i]) {
                distance[u->i] = distance[v->i] + weight;
                priority_queue_nq(q, u, -distance[u->i]);

                for(int i = 0; i < graph_vertex_in_degree(u); i++) {
                    graph_remove_edge(acyclic_product, vec_get(u->in, i), u);
                }
            } else if(distance[v->i] + weight > distance[u->i]) {
                continue;
            }
            graph_add_edge(acyclic_product, graph_edge_between(graph, v, u), v, u);
        }
    }

    priority_queue_free(q, NULL);
}

// similar to dijkstra's acyclic product, all dynamic programming problems result in an acyclic graph where
// each node represents a state and the edges represent a path taken from that state
