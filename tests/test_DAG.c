#include "../headers/acyclic_graph.h"
#include "../headers/graph_strong_connectivity.h"
#include "orange_juice.h"
#include "../headers/logging.h"

oj_test(DAG_topological_sort_returns_a_topologically_sorted_array_of_vertices) {
    struct graph g = graph_new();
    int v[6] = { 1, 2, 3, 4, 5, 6 };
    for(int i = 0; i < 6; i++) {
        graph_add_vertex(&g, v + i);
    }
    graph_add_edge(&g, v+3, v+0, 1);
    graph_add_edge(&g, v+3, v+4, 1);
    graph_add_edge(&g, v+0, v+1, 1);
    graph_add_edge(&g, v+4, v+1, 1);
    graph_add_edge(&g, v+1, v+2, 1);
    graph_add_edge(&g, v+4, v+2, 1);
    graph_add_edge(&g, v+2, v+5, 1);

    vector(void*) order = vec_new(void*);
    acyclic_graph_toplogical_sort(&g, order);

    void* topological_order[6] = { v+3, v+4, v+0, v+1, v+2, v+5 };
    oj_assert_eq_bytes(6 * sizeof(int), topological_order, vec_as_array(order), "");

    vec_free(order, NULL);
    graph_free(&g);

    oj_fresh;
}

oj_test(graph_kosaraju_returns_strongly_connected_components_of_DAG) {
    struct graph g = graph_new();
    int v[7] = { 1, 2, 3, 4, 5, 6, 7 };
    for(int i = 0; i < 7; i++) {
        graph_add_vertex(&g, v + i);
    }
    graph_add_edge(&g, v+0, v+1, 1);
    graph_add_edge(&g, v+1, v+0, 1);
    graph_add_edge(&g, v+1, v+2, 1);
    graph_add_edge(&g, v+2, v+5, 1);
    graph_add_edge(&g, v+5, v+6, 1);
    graph_add_edge(&g, v+6, v+2, 1);
    graph_add_edge(&g, v+3, v+0, 1);
    graph_add_edge(&g, v+3, v+4, 1);
    graph_add_edge(&g, v+4, v+1, 1);
    graph_add_edge(&g, v+4, v+5, 1);


    void* roots[graph_vertices_len(&g)];
    struct graph condensed_graph = graph_new();
    int result = graph_kosaraju(&g, roots, &condensed_graph);

    oj_assert(vec_contains(condensed_graph.vertices, v+0), "");
    oj_assert(vec_contains(condensed_graph.vertices, v+2), "");
    oj_assert(vec_contains(condensed_graph.vertices, v+3), "");
    oj_assert(vec_contains(condensed_graph.vertices, v+4), "");
    oj_assert_eq_int(4, result);

    graph_free(&g);
    graph_free(&condensed_graph);
    oj_fresh;
}

oj_prepare(test_DAG_strongly_connected_components) {
    oj_run(graph_kosaraju_returns_strongly_connected_components_of_DAG);
    oj_report;
    oj_fresh;
}

oj_prepare(test_DAG_topological_sort) {
    oj_run(DAG_topological_sort_returns_a_topologically_sorted_array_of_vertices);
    oj_report;
    oj_fresh;
}

int main() {
    oj_blend(test_DAG_topological_sort, 0);
    oj_blend(test_DAG_strongly_connected_components, 0);
    return 0;
}
