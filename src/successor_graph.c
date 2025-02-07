#include "../headers/successor_graph.h"

int successor_graph_precalculate_succ_i(struct graph* graph, int vertex_i, int limit, int** succ) {
    struct vertex* v = graph_vertex_from_i(graph, vertex_i);
    succ[log_2(limit)][vertex_i] = limit == 1 
        ? vec_get(v->out, 0)->i
        : successor_graph_precalculate_succ_i(
            graph,
            successor_graph_precalculate_succ_i(graph, v->i, limit/2, succ), limit/2, succ
        );
    return succ[log_2(limit)][vertex_i];
}

void successor_graph_precalculate_succ(struct graph* successor_graph, int limit, int** succ) {
    for(int i = 0; i < graph_vertices_len(successor_graph); i++) {
        successor_graph_precalculate_succ_i(successor_graph, i, limit, succ);
    }
}

struct vertex* successor_graph_succ(struct vertex* v) {
    return vec_get(v->out, 0);
}

int successor_graph_succ_n(struct vertex* v, int k, int** succ) {
    if(k == 1) {
        return successor_graph_succ(v)->i;
    }
    if(succ == NULL) {
        return successor_graph_succ_n(vec_get(v->out, 0), k - 1, NULL);
    }
    int kth_successor = k;
    while(k > 0) {
        kth_successor = succ[log_2(k)][v->i];
        k /= 2;
    }
    return kth_successor;
}


void successor_graph_floyd_tortoise_and_hair(struct graph* successor_graph, int* first_vertex_index, int* cycle_length) {
    //cycle detection
    struct vertex* a = successor_graph_succ(graph_vertex_from_i(successor_graph, 0));
    struct vertex* b = successor_graph_succ(successor_graph_succ(graph_vertex_from_i(successor_graph, 0)));
    while(a != b) {
        a = successor_graph_succ(a);
        b = successor_graph_succ(successor_graph_succ(b));
    }

    //first node of cycle
    a = graph_vertex_from_i(successor_graph, 0);
    while(a != b) {
        a = successor_graph_succ(a);
        b = successor_graph_succ(b);
    }
    *first_vertex_index = a->i;

    //length of cycle
    b = successor_graph_succ(a);
    int length = 1;
    while (a != b) {
        b = successor_graph_succ(b);
        ++length;
    }
    *cycle_length = length;
}
