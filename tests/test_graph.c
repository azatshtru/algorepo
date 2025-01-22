#include "../headers/graph.h"
#include "orange_juice.h"

oj_test(graph_allocates) {
    struct graph g = graph_new();
    oj_assert(g.edges != NULL, "graph edges didn't allocate properly");
    oj_assert(g.vertices != NULL, "graph vertices didn't allocate properly");
    graph_free(&g);
    oj_fresh;
}

oj_test(graph_edge_insert) {
    struct graph g = graph_new();
    struct vertex* v1 = graph_add_vertex(&g);
    struct vertex* v2 = graph_add_vertex(&g);
    struct edge* e = graph_add_edge(&g, v1, v2);
    oj_assert(e->from == v1, "");
    oj_assert(e->to == v2, "");
    graph_remove_edge(&g, v1, v2);
    graph_free(&g);
    oj_fresh;
}

oj_test(graph_vertex_allocates) {
    struct graph g = graph_new();
    struct vertex* vertex = graph_add_vertex(&g);
    oj_assert(&vertex != NULL, "vertex didn't allocate properly");
    oj_assert(vertex->out != NULL, "neighbors vectors didn't allocate properly");
    oj_assert(vertex->in != NULL, "neighbors vectors didn't allocate properly");
    oj_assert_eq_int(0, vertex->i);
    graph_free(&g);
    oj_fresh;
}

oj_test(graph_allocate_two_vertices) {
    struct graph g = graph_new();
    struct vertex* v1 = graph_add_vertex(&g);
    struct vertex* v2 = graph_add_vertex(&g);
    oj_assert_eq_int(0, v1->i);
    oj_assert_eq_int(1, v2->i);
    graph_free(&g);
    oj_fresh;
}

oj_test(test_graph_edge_hash) {
    struct graph g = graph_new();
    struct vertex* v1 = graph_add_vertex(&g);
    struct vertex* v2 = graph_add_vertex(&g);
    struct edge* e1 = graph_add_edge(&g, v1, v2);
    struct edge* e2 = graph_add_edge(&g, v2, v1);
    int result1 = graph_edge_hash(&e1);
    int result2 = ((struct hashset*)g.edges)->hash_fn(&e2);
    graph_free(&g);
    oj_assert_eq_int(2, result1);
    oj_assert_eq_int(1, result2);
    oj_fresh;
}

oj_test(test_graph_edge_cmp) {
    struct graph g = graph_new();
    struct vertex* v1 = graph_add_vertex(&g);
    struct vertex* v2 = graph_add_vertex(&g);
    struct vertex* v3 = graph_add_vertex(&g);
    struct edge* e1 = graph_add_edge(&g, v1, v2);
    struct edge* e2 = graph_add_edge(&g, v2, v1);
    struct edge* e3 = graph_add_edge(&g, v3, v1);
    struct edge* e4 = graph_add_edge(&g, v1, v2);
    oj_assert_eq_int(0, graph_edge_cmp(&e1, &e2));
    oj_assert_eq_int(0, graph_edge_cmp(&e2, &e3));
    oj_assert_eq_int(1, graph_edge_cmp(&e1, &e4));
    graph_free(&g);
    oj_fresh;
}

oj_test(graph_insert_3_edges) {
    struct graph g = graph_new();
    struct vertex* v1 = graph_add_vertex(&g);
    struct vertex* v2 = graph_add_vertex(&g);
    struct vertex* v3 = graph_add_vertex(&g);
    struct edge* e1 = graph_add_edge(&g, v1, v2);
    struct edge* e2 = graph_add_edge(&g, v1, v3);
    struct edge* e3 = graph_add_edge(&g, v2, v3);
    oj_assert(e1->from == v1 && e1->to == v2, "");
    oj_assert(e2->from == v1 && e2->to == v3, "");
    oj_assert(e3->from == v2 && e3->to == v3, "");
    graph_free(&g);
    oj_fresh;
}

oj_test(test_graph_remove_vertex) {
    struct graph g = graph_new();
    struct vertex* v1 = graph_add_vertex(&g);
    struct vertex* v2 = graph_add_vertex(&g);
    struct edge* e1 = graph_add_edge(&g, v1, v2);
    struct edge* e2 = graph_add_edge(&g, v2, v1);
    oj_assert_eq_int(2, graph_vertices_len(&g));
    oj_assert_eq_int(2, graph_edges_len(&g));
    graph_remove_vertex(&g, v1);
    oj_assert_eq_int(1, graph_vertices_len(&g));
    oj_assert_eq_int(0, graph_edges_len(&g));
    oj_fresh;
}

oj_test(graph_length_queries_return_number_of_vertices_and_edges) {
    struct graph g = graph_new();
    struct vertex* v1 = graph_add_vertex(&g);
    struct vertex* v2 = graph_add_vertex(&g);
    struct vertex* v3 = graph_add_vertex(&g);
    struct edge* e1 = graph_add_edge(&g, v1, v2);
    struct edge* e2 = graph_add_edge(&g, v2, v1);
    struct edge* e3 = graph_add_edge(&g, v3, v1);
    struct edge* e4 = graph_add_edge(&g, v1, v2);
    oj_assert_eq_int(3, graph_vertices_len(&g));
    oj_assert_eq_int(3, graph_edges_len(&g));
    graph_free(&g);
    oj_fresh;
}

oj_test(graph_length_queries_after_mutation) {
    struct graph g = graph_new();
    struct vertex* v1 = graph_add_vertex(&g);
    struct vertex* v2 = graph_add_vertex(&g);
    struct vertex* v3 = graph_add_vertex(&g);
    struct vertex* v4 = graph_add_vertex(&g);
    struct edge* e1 = graph_add_edge(&g, v1, v2);
    struct edge* e2 = graph_add_edge(&g, v2, v1);
    struct edge* e3 = graph_add_edge(&g, v3, v1);
    struct edge* e4 = graph_add_edge(&g, v1, v2);
    struct edge* e5 = graph_add_edge(&g, v2, v4);
    oj_assert_eq_int(4, graph_vertices_len(&g));
    oj_assert_eq_int(4, graph_edges_len(&g));

    graph_remove_edge(&g, v1, v2);
    oj_assert_eq_int(3, graph_edges_len(&g));

    graph_remove_vertex(&g, v1);
    oj_assert_eq_int(3, graph_vertices_len(&g));
    oj_assert_eq_int(1, graph_edges_len(&g));

    struct edge* e6 = graph_add_edge(&g, v2, v3);
    struct edge* e7 = graph_add_edge(&g, v4, v3);
    oj_assert_eq_int(3, graph_edges_len(&g));

    graph_remove_vertex(&g, v2);
    oj_assert_eq_int(1, graph_edges_len(&g));

    graph_remove_edge(&g, v3, v4);
    oj_assert_eq_int(1, graph_edges_len(&g));

    graph_remove_vertex(&g, v3);
    graph_remove_vertex(&g, v3);
    oj_assert_eq_int(0, graph_edges_len(&g));

    graph_free(&g);
    oj_fresh;
}

oj_test(test_graph_vertex_id_queries) {
    oj_fresh;
}

oj_test(graph_add_int_vertex) {
    oj_fresh;
}

oj_prepare(graph_setup_tests) {
    oj_run(graph_allocates);
    oj_run(graph_vertex_allocates);
    oj_run(graph_allocate_two_vertices);
    oj_run(graph_edge_insert);
    oj_run(graph_insert_3_edges);
    oj_run(test_graph_edge_hash);
    oj_run(test_graph_edge_cmp);
    oj_run(test_graph_remove_vertex);
    oj_report;
    oj_fresh;
}

oj_prepare(graph_query_tests) {
    oj_run(graph_length_queries_return_number_of_vertices_and_edges);
    oj_run(graph_length_queries_after_mutation);
    oj_run(test_graph_vertex_id_queries);
    oj_report;
    oj_fresh;
}


int main() {
    oj_blend(graph_setup_tests, 0);
    oj_blend(graph_query_tests, 0);
    return 0;
}
