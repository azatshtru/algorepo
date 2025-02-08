#include "../headers/acyclic_graph.h"

int acyclic_graph_topological_sort_reversed(struct graph* graph, void* v, int* state, void** topological_order, int topological_order_index) {
    struct vertex* vadj = graph_vertex(graph, v);
    if(state[vadj->i] == PROCESSED) return 1;
    if(state[vadj->i] == PROCESSING) return 0;
    int is_acyclic;
    state[vadj->i] = PROCESSING;
    for(int i = 0; i < graph_vertex_out_degree(graph, v); i++) {
        void* u = vec_get(vadj->out, i)->value;
        is_acyclic = acyclic_graph_topological_sort_reversed(graph, u, state, topological_order, topological_order_index);
        if(is_acyclic == 0) break;
    }
    state[vadj->i] = PROCESSED;
    if(topological_order != NULL) {
        topological_order[topological_order_index++] = v;
    }
    return is_acyclic;
}

int acyclic_graph_toplogical_sort(struct graph* graph, void** topological_order) {
    int vertex_len = graph_vertices_len(graph);
    int state[vertex_len];
    for(int i = 0; i < vertex_len; i++) {
        state[i] = 0;
    }
    for(int i = 0; i < vertex_len; i++) {
        if(state[i] != 0) { continue; }
        if(acyclic_graph_topological_sort_reversed(graph, vec_get(graph->vertices, i), state, topological_order, 0)) {
            continue;
        } else {
            return 1;
        }
    }
    for(int i = 0, j = vertex_len - 1; i < j; i++, j--) {
        swap(topological_order + i, topological_order + j, sizeof(void*));
    }
    return 0;
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
