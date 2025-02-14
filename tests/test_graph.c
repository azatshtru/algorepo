#include "../headers/graph.h"
#include "orange_juice.h"

oj_test(graph_allocates) {
    struct graph g = graph_new();
    oj_assert(g.edges != NULL, "graph edges didn't allocate properly");
    oj_assert(g.adjacency_list != NULL, "graph vertices didn't allocate properly");
    graph_free(&g);
    oj_fresh;
}

oj_test(graph_vertex_allocates) {
    struct graph g = graph_new();
    int vertex = 1;
    graph_add_vertex(&g, &vertex);
    oj_assert(&vertex != NULL, "vertex didn't allocate properly");
    graph_free(&g);
    oj_fresh;
}


oj_test(graph_edge_insert) {
    struct graph g = graph_new();
    int v1 = 0;
    int v2 = 1;
    graph_add_vertex(&g, &v1);
    graph_add_vertex(&g, &v2);
    graph_add_edge(&g, &v1, &v2, 1);
    struct edge* e = graph_edge_between(&g, &v1, &v2);
    oj_assert(e->from == &v1, "");
    oj_assert(e->to == &v2, "");
    graph_remove_edge(&g, &v1, &v2);
    graph_free(&g);
    oj_fresh;
}

oj_test(graph_insert_3_edges) {
    struct graph g = graph_new();
    int v1 = 1;
    int v2 = 2;
    int v3 = 3;
    graph_add_vertex(&g, &v1);
    graph_add_vertex(&g, &v2);
    graph_add_vertex(&g, &v3);
    graph_add_edge(&g, &v1, &v2, 1);
    graph_add_edge(&g, &v1, &v3, 1);
    graph_add_edge(&g, &v2, &v3, 1);
    oj_assert_eq_int(3, graph_edges_len(&g));
    struct edge* e1 = graph_edge_between(&g, &v1, &v2);
    struct edge* e2 = graph_edge_between(&g, &v1, &v3);
    struct edge* e3 = graph_edge_between(&g, &v2, &v3);
    oj_assert(e1->from == &v1 && e1->to == &v2, "");
    oj_assert(e2->from == &v1 && e2->to == &v3, "");
    oj_assert(e3->from == &v2 && e3->to == &v3, "");
    graph_free(&g);
    oj_fresh;
}

oj_test(test_graph_remove_vertex) {
    struct graph g = graph_new();
    int v1 = 1;
    int v2 = 2;
    int v3 = 3;
    graph_add_vertex(&g, &v1);
    graph_add_vertex(&g, &v2);
    graph_add_edge(&g, &v1, &v2, 1);
    graph_add_edge(&g, &v2, &v1, 1);
    oj_assert_eq_int(2, graph_vertices_len(&g));
    oj_assert_eq_int(2, graph_edges_len(&g));
    graph_remove_vertex(&g, &v1);
    oj_assert_eq_int(1, graph_vertices_len(&g));
    oj_assert_eq_int(0, graph_edges_len(&g));
    oj_fresh;
}

oj_test(graph_length_queries_return_number_of_vertices_and_edges) {
    struct graph g = graph_new();
    int v1 = 1;
    int v2 = 2;
    int v3 = 3;
    graph_add_vertex(&g, &v1);
    graph_add_vertex(&g, &v2);
    graph_add_vertex(&g, &v3);
    graph_add_edge(&g, &v1, &v2, 1);
    graph_add_edge(&g, &v2, &v1, 1);
    graph_add_edge(&g, &v3, &v1, 1);
    graph_add_edge(&g, &v1, &v2, 1);
    oj_assert_eq_int(3, graph_vertices_len(&g));
    oj_assert_eq_int(3, graph_edges_len(&g));
    graph_free(&g);
    oj_fresh;
}

oj_test(graph_length_queries_after_mutation) {
    struct graph g = graph_new();
    int v1 = 1;
    int v2 = 2;
    int v3 = 3;
    int v4 = 4;
    graph_add_vertex(&g, &v1);
    graph_add_vertex(&g, &v2);
    graph_add_vertex(&g, &v3);
    graph_add_vertex(&g, &v4);
    graph_add_edge(&g, &v1, &v2, 1);
    graph_add_edge(&g, &v2, &v1, 1);
    graph_add_edge(&g, &v3, &v1, 1);
    graph_add_edge(&g, &v1, &v2, 1);
    graph_add_edge(&g, &v2, &v4, 1);
    oj_assert_eq_int(4, graph_vertices_len(&g));
    oj_assert_eq_int(4, graph_edges_len(&g));

    graph_remove_edge(&g, &v1, &v2);
    oj_assert_eq_int(3, graph_edges_len(&g));

    graph_remove_vertex(&g, &v1);
    oj_assert_eq_int(3, graph_vertices_len(&g));
    oj_assert_eq_int(1, graph_edges_len(&g));

    graph_add_edge(&g, &v2, &v3, 1);
    graph_add_edge(&g, &v4, &v3, 1);
    oj_assert_eq_int(3, graph_edges_len(&g));

    graph_remove_vertex(&g, &v2);
    oj_assert_eq_int(1, graph_edges_len(&g));

    graph_remove_edge(&g, &v3, &v4);
    oj_assert_eq_int(1, graph_edges_len(&g));

    graph_remove_vertex(&g, &v3);
    oj_assert_eq_int(0, graph_edges_len(&g));

    graph_free(&g);
    oj_fresh;
}

oj_test(test_graph_edge_between) {
    struct graph g = graph_new();
    int v1 = 1;
    int v2 = 2;
    int v3 = 3;
    int v4 = 4;
    graph_add_vertex(&g, &v1);
    graph_add_vertex(&g, &v2);
    graph_add_vertex(&g, &v3);
    graph_add_vertex(&g, &v4);
    graph_add_edge(&g, &v1, &v2, 1);
    graph_add_edge(&g, &v2, &v1, 1);
    graph_add_edge(&g, &v3, &v1, 1);
    graph_add_edge(&g, &v1, &v2, 1);
    graph_add_edge(&g, &v2, &v4, 1);

    oj_assert(graph_edge_between(&g, &v1, &v2) != NULL, "");
    oj_assert(graph_edge_between(&g, &v2, &v1) != NULL, "");
    oj_assert(graph_edge_between(&g, &v2, &v3) == NULL, "");
    oj_assert(graph_edge_between(&g, &v2, &v4) != NULL, "");
    oj_assert(graph_edge_between(&g, &v3, &v1) != NULL, "");

    graph_remove_edge(&g, &v1, &v2);
    oj_assert(graph_edge_between(&g, &v2, &v1) != NULL, "");
    oj_assert(graph_edge_between(&g, &v1, &v2) == NULL, "");

    graph_remove_vertex(&g, &v1);
    oj_assert(graph_edge_between(&g, &v2, &v1) == NULL, "");
    oj_assert(graph_edge_between(&g, &v1, &v2) == NULL, "");
    oj_assert(graph_edge_between(&g, &v1, &v3) == NULL, "");
    oj_assert(graph_edge_between(&g, &v3, &v1) == NULL, "");
    oj_assert(graph_edge_between(&g, &v2, &v4) != NULL, "");

    graph_add_edge(&g, &v2, &v3, 1);
    graph_add_edge(&g, &v4, &v3, 1);
    oj_assert(graph_edge_between(&g, &v2, &v3) != NULL, "");
    oj_assert(graph_edge_between(&g, &v4, &v3) != NULL, "");
    oj_assert(graph_edge_between(&g, &v3, &v4) == NULL, "");

    graph_free(&g);
    oj_fresh;
}

oj_test(test_graph_adjacent_vertices) {
    struct graph g = graph_new();
    int v1;
    int v2;
    int v3;
    int v4;
    graph_add_vertex(&g, &v1);
    graph_add_vertex(&g, &v2);
    graph_add_vertex(&g, &v3);
    graph_add_vertex(&g, &v4);
    graph_add_edge(&g, &v1, &v2, 1);
    graph_add_edge(&g, &v2, &v1, 1);
    graph_add_edge(&g, &v3, &v1, 1);
    graph_add_edge(&g, &v1, &v2, 1);
    graph_add_edge(&g, &v2, &v4, 1);

    oj_assert_eq_int(1, graph_vertices_are_adjacent(&g, &v1, &v2));
    oj_assert_eq_int(1, graph_vertices_are_adjacent(&g, &v2, &v1));
    oj_assert_eq_int(1, graph_vertices_are_adjacent(&g, &v3, &v1));
    oj_assert_eq_int(1, graph_vertices_are_adjacent(&g, &v1, &v3));
    oj_assert_eq_int(0, graph_vertices_are_adjacent(&g, &v2, &v3));
    oj_assert_eq_int(0, graph_vertices_are_adjacent(&g, &v4, &v3));
    oj_assert_eq_int(0, graph_vertices_are_adjacent(&g, &v1, &v4));
    oj_assert_eq_int(1, graph_vertices_are_adjacent(&g, &v4, &v2));
    oj_assert_eq_int(1, graph_vertices_are_adjacent(&g, &v2, &v4));

    graph_remove_edge(&g, &v1, &v2);
    oj_assert_eq_int(1, graph_vertices_are_adjacent(&g, &v1, &v2));
    oj_assert_eq_int(1, graph_vertices_are_adjacent(&g, &v2, &v1));

    graph_remove_vertex(&g, &v1);
    oj_assert_eq_int(0, graph_vertices_are_adjacent(&g, &v1, &v2));
    oj_assert_eq_int(0, graph_vertices_are_adjacent(&g, &v2, &v1));

    graph_add_edge(&g, &v2, &v3, 1);
    graph_add_edge(&g, &v4, &v3, 1);
    oj_assert_eq_int(1, graph_vertices_are_adjacent(&g, &v2, &v3));
    oj_assert_eq_int(1, graph_vertices_are_adjacent(&g, &v4, &v3));

    graph_free(&g);
    oj_fresh;
}

oj_test(test_graph_degree_queries) {
    struct graph g = graph_new();
    int v1 = 1;
    int v2 = 2;
    int v3 = 3;
    int v4 = 4;
    graph_add_vertex(&g, &v1);
    graph_add_vertex(&g, &v2);
    graph_add_vertex(&g, &v3);
    graph_add_vertex(&g, &v4);
    graph_add_edge(&g, &v1, &v2, 1);
    graph_add_edge(&g, &v2, &v1, 1);
    graph_add_edge(&g, &v3, &v1, 1);
    graph_add_edge(&g, &v1, &v2, 1);
    graph_add_edge(&g, &v2, &v4, 1);

    oj_assert_eq_int(1, graph_vertex_out_degree(&g, &v1));
    oj_assert_eq_int(2, graph_vertex_in_degree(&g, &v1));
    oj_assert_eq_int(2, graph_vertex_out_degree(&g, &v2));
    oj_assert_eq_int(1, graph_vertex_in_degree(&g, &v2));
    oj_assert_eq_int(1, graph_vertex_out_degree(&g, &v3));
    oj_assert_eq_int(0, graph_vertex_in_degree(&g, &v3));
    oj_assert_eq_int(0, graph_vertex_out_degree(&g, &v4));
    oj_assert_eq_int(1, graph_vertex_in_degree(&g, &v4));

    graph_remove_vertex(&g, &v1);
    oj_assert_eq_int(1, graph_vertex_out_degree(&g, &v2));
    oj_assert_eq_int(0, graph_vertex_in_degree(&g, &v2));
    oj_assert_eq_int(0, graph_vertex_out_degree(&g, &v3));
    oj_assert_eq_int(0, graph_vertex_in_degree(&g, &v3));

    graph_add_edge(&g, &v2, &v3, 1);
    graph_add_edge(&g, &v4, &v3, 1);
    oj_assert_eq_int(2, graph_vertex_out_degree(&g, &v2));
    oj_assert_eq_int(1, graph_vertex_out_degree(&g, &v4));
    oj_assert_eq_int(2, graph_vertex_in_degree(&g, &v3));

    graph_remove_edge(&g, &v2, &v3);
    oj_assert_eq_int(1, graph_vertex_out_degree(&g, &v2));
    oj_assert_eq_int(1, graph_vertex_in_degree(&g, &v3));
    oj_assert_eq_int(1, graph_vertex_in_degree(&g, &v4));

    oj_fresh;
}

oj_prepare(graph_setup_tests) {
    oj_run(graph_allocates);
    oj_report;
    oj_fresh;
}

oj_prepare(graph_mutation_tests) {
    oj_run(graph_vertex_allocates);
    oj_run(graph_edge_insert);
    oj_run(graph_insert_3_edges);
    oj_run(test_graph_remove_vertex);
    oj_report;
    oj_fresh;
}

oj_prepare(graph_query_tests) {
    oj_run(graph_length_queries_return_number_of_vertices_and_edges);
    oj_run(graph_length_queries_after_mutation);
    oj_run(test_graph_edge_between);
    oj_run(test_graph_adjacent_vertices);
    oj_run(test_graph_degree_queries);
    oj_report;
    oj_fresh;
}


int main() {
    oj_blend(graph_setup_tests, 0);
    oj_blend(graph_mutation_tests, 0);
    oj_blend(graph_query_tests, 0);
    return 0;
}
