#include "../headers/graph_paths_and_circuits.h"

int graph_eulerian_path_exists(struct graph* graph, struct vertex** start_vertex) {
    struct vertex* start = NULL;
    struct vertex* end = NULL;
    int vertex_len = graph_vertices_len(graph);

    for (int i = 0; i < vertex_len; i++) {
        struct vertex* v = graph_vertex_from_i(graph, i);
        if(graph_vertex_out_degree(v) - graph_vertex_in_degree(v) == 1) {
            if(start) { return 0; }
            start = v;
        } else if(graph_vertex_in_degree(v) - graph_vertex_out_degree(v) == 1) {
            if(end) { return 0; }
            end = v;
        } else if (graph_vertex_out_degree(v) != graph_vertex_in_degree(v)) {
            return 0;
        }
    }
    *start_vertex = start;
    return 1;
}

void graph_hierholzer(struct graph* graph, struct edge** eulerian_path) {
    struct vertex* start;
    if(!graph_eulerian_path_exists(graph, &start)) {
        return;
    }
    if(start == NULL) {
        start = graph_vertex_from_i(graph, 0);
    }

    VecDeque(struct vertex*) stack = queue_new(struct vertex*);
    vector(struct vertex*) path = vec_new(struct vertex*);
    int processed[graph_vertices_len(graph)];
    memzero(processed, sizeof(int) * graph_vertices_len(graph));

    queue_push_back(stack, start);
    while(!queue_is_empty(stack)) {
        struct vertex* v = queue_back(stack);
        
        if(processed[v->i] < vec_len(v->out)) {
            queue_push_back(stack, graph_vertex_from_i(graph, processed[v->i]++));
        } else {
            vec_push(path, queue_pop_back(stack));
        }
    }

    int j = 0;
    struct vertex* last_vertex = vec_pop(path, -1);
    for (int i = vec_len(path) - 2; i >= 0; i--) {
        struct vertex* current_vertex = vec_pop(path, -1);
        eulerian_path[j++] = graph_edge_between(graph, last_vertex, current_vertex);
        last_vertex = current_vertex;
    }
}
