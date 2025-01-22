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
    struct vertex v1;
    struct vertex v2;
    graph_add_vertex(&g, &v1);
    graph_add_vertex(&g, &v2);
    struct edge e;
    graph_add_edge(&g, &e, &v1, &v2);
    oj_assert(e.from == &v1, "");
    oj_assert(e.to == &v2, "");
    graph_remove_edge(&g, &v1, &v2);
    graph_free(&g);
    oj_fresh;
}

oj_test(graph_vertex_allocates) {
    struct graph g = graph_new();
    struct vertex vertex;
    graph_add_vertex(&g, &vertex);
    oj_assert(&vertex != NULL, "vertex didn't allocate properly");
    oj_assert(vertex.out != NULL, "neighbors vectors didn't allocate properly");
    oj_assert(vertex.in != NULL, "neighbors vectors didn't allocate properly");
    oj_assert_eq_int(0, vertex.i);
    graph_free(&g);
    oj_fresh;
}

oj_test(graph_allocate_two_vertices) {
    struct graph g = graph_new();
    struct vertex v1;
    graph_add_vertex(&g, &v1);
    struct vertex v2;
    graph_add_vertex(&g, &v2);
    oj_assert_eq_int(0, v1.i);
    oj_assert_eq_int(1, v2.i);
    graph_free(&g);
    oj_fresh;
}

oj_test(test_graph_edge_hash) {
    struct graph g = graph_new();
    struct vertex v1;
    graph_add_vertex(&g, &v1);
    struct vertex v2;
    graph_add_vertex(&g, &v2);
    struct edge e1;
    graph_add_edge(&g, &e1, &v1, &v2);
    struct edge e2;
    graph_add_edge(&g, &e2, &v2, &v1);
    struct edge* e1ptr = &e1;
    struct edge* e2ptr = &e2;
    int result1 = graph_edge_hash(&e1ptr);
    int result2 = ((struct hashset*)g.edges)->hash_fn(&e2ptr);
    graph_free(&g);
    oj_assert_eq_int(2, result1);
    oj_assert_eq_int(1, result2);
    oj_fresh;
}

oj_test(test_graph_edge_cmp) {
    struct graph g = graph_new();
    struct vertex v1;
    graph_add_vertex(&g, &v1);
    struct vertex v2;
    graph_add_vertex(&g, &v2);
    struct vertex v3;
    graph_add_vertex(&g, &v3);
    struct edge e1;
    graph_add_edge(&g, &e1, &v1, &v2);
    struct edge e2;
    graph_add_edge(&g, &e2, &v2, &v1);
    struct edge e3;
    graph_add_edge(&g, &e3, &v3, &v1);
    struct edge e4;
    graph_add_edge(&g, &e4, &v1, &v2);

    struct edge* edges[4];
    edges[0] = &e1;
    edges[1] = &e2;
    edges[2] = &e3;
    edges[3] = &e4;

    oj_assert_eq_int(0, graph_edge_cmp(edges+0, edges+1));
    oj_assert_eq_int(0, graph_edge_cmp(edges+1, edges+2));
    oj_assert_eq_int(1, graph_edge_cmp(edges+0, edges+3));
    graph_free(&g);
    oj_fresh;
}

oj_test(graph_insert_3_edges) {
    struct graph g = graph_new();
    struct vertex v1;
    graph_add_vertex(&g, &v1);
    struct vertex v2;
    graph_add_vertex(&g, &v2);
    struct vertex v3;
    graph_add_vertex(&g, &v3);
    struct edge e1;
    graph_add_edge(&g, &e1, &v1, &v2);
    struct edge e2;
    graph_add_edge(&g, &e2, &v1, &v3);
    struct edge e3;
    graph_add_edge(&g, &e3, &v2, &v3);
    oj_assert(e1.from == &v1 && e1.to == &v2, "");
    oj_assert(e2.from == &v1 && e2.to == &v3, "");
    oj_assert(e3.from == &v2 && e3.to == &v3, "");
    graph_free(&g);
    oj_fresh;
}

oj_test(test_graph_remove_vertex) {
    struct graph g = graph_new();
    struct vertex v1;
    graph_add_vertex(&g, &v1);
    struct vertex v2;
    graph_add_vertex(&g, &v2);
    struct edge e1;
    graph_add_edge(&g, &e1, &v1, &v2);
    struct edge e2;
    graph_add_edge(&g, &e2, &v2, &v1);
    oj_assert_eq_int(2, graph_vertices_len(&g));
    oj_assert_eq_int(2, graph_edges_len(&g));
    graph_remove_vertex(&g, &v1);
    oj_assert_eq_int(1, graph_vertices_len(&g));
    oj_assert_eq_int(0, graph_edges_len(&g));
    oj_fresh;
}

oj_test(graph_length_queries_return_number_of_vertices_and_edges) {
    struct graph g = graph_new();
    struct vertex v1;
    graph_add_vertex(&g, &v1);
    struct vertex v2;
    graph_add_vertex(&g, &v2);
    struct vertex v3;
    graph_add_vertex(&g, &v3);
    struct edge e1;
    graph_add_edge(&g, &e1, &v1, &v2);
    struct edge e2;
    graph_add_edge(&g, &e2, &v2, &v1);
    struct edge e3;
    graph_add_edge(&g, &e3, &v3, &v1);
    struct edge e4;
    graph_add_edge(&g, &e4, &v1, &v2);
    oj_assert_eq_int(3, graph_vertices_len(&g));
    oj_assert_eq_int(3, graph_edges_len(&g));
    graph_free(&g);
    oj_fresh;
}

oj_test(graph_length_queries_after_mutation) {
    struct graph g = graph_new();
    struct vertex v1;
    graph_add_vertex(&g, &v1);
    struct vertex v2;
    graph_add_vertex(&g, &v2);
    struct vertex v3;
    graph_add_vertex(&g, &v3);
    struct vertex v4;
    graph_add_vertex(&g, &v4);
    struct edge e1;
    graph_add_edge(&g, &e1, &v1, &v2);
    struct edge e2;
    graph_add_edge(&g, &e2, &v2, &v1);
    struct edge e3;
    graph_add_edge(&g, &e3, &v3, &v1);
    struct edge e4;
    graph_add_edge(&g, &e4, &v1, &v2);
    struct edge e5;
    graph_add_edge(&g, &e5, &v2, &v4);
    oj_assert_eq_int(4, graph_vertices_len(&g));
    oj_assert_eq_int(4, graph_edges_len(&g));

    graph_remove_edge(&g, &v1, &v2);
    oj_assert_eq_int(3, graph_edges_len(&g));

    graph_remove_vertex(&g, &v1);
    oj_assert_eq_int(3, graph_vertices_len(&g));
    oj_assert_eq_int(1, graph_edges_len(&g));

    struct edge e6;
    graph_add_edge(&g, &e6, &v2, &v3);
    struct edge e7;
    graph_add_edge(&g, &e7, &v4, &v3);
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

oj_test(test_graph_vertex_id_queries) {
    struct graph g = graph_new();
    struct vertex v1;
    graph_add_vertex(&g, &v1);
    struct vertex v2;
    graph_add_vertex(&g, &v2);
    struct vertex v3;
    graph_add_vertex(&g, &v3);
    struct vertex v4;
    graph_add_vertex(&g, &v4);
    oj_assert_eq_int(4, graph_vertices_len(&g));

    oj_assert_eq_int(0, v1.i);
    oj_assert_eq_int(1, v2.i);
    oj_assert_eq_int(2, v3.i);
    oj_assert_eq_int(3, v4.i);
    oj_assert_eq_pointer(&v1, graph_vertex_from_i(&g, 0));
    oj_assert_eq_pointer(&v2, graph_vertex_from_i(&g, 1));
    oj_assert_eq_pointer(&v3, graph_vertex_from_i(&g, 2));
    oj_assert_eq_pointer(&v4, graph_vertex_from_i(&g, 3));

    graph_remove_vertex(&g, &v3);
    oj_assert_eq_int(3, graph_vertices_len(&g));
    oj_assert_eq_pointer(NULL, graph_vertex_from_i(&g, 2));

    struct vertex v5;
    graph_add_vertex(&g, &v5);
    oj_assert_eq_int(2, v5.i);
    oj_assert_eq_pointer(&v5, graph_vertex_from_i(&g, 2));

    graph_remove_vertex(&g, &v2);
    oj_assert_eq_int(3, graph_vertices_len(&g));
    oj_assert_eq_pointer(NULL, graph_vertex_from_i(&g, 1));

    graph_remove_vertex(&g, &v5);
    oj_assert_eq_int(2, graph_vertices_len(&g));
    oj_assert_eq_pointer(NULL, graph_vertex_from_i(&g, 2));
    
    struct vertex v6;
    graph_add_vertex(&g, &v6);
    oj_assert_eq_int(2, v6.i);
    oj_assert_eq_pointer(&v6, graph_vertex_from_i(&g, 2));

    struct vertex v7;
    graph_add_vertex(&g, &v7);
    oj_assert_eq_int(1, v7.i);
    oj_assert_eq_pointer(&v7, graph_vertex_from_i(&g, 1));

    graph_free(&g);
    oj_fresh;
}

oj_test(test_graph_edge_between) {
    struct graph g = graph_new();
    struct vertex v1;
    graph_add_vertex(&g, &v1);
    struct vertex v2;
    graph_add_vertex(&g, &v2);
    struct vertex v3;
    graph_add_vertex(&g, &v3);
    struct vertex v4;
    graph_add_vertex(&g, &v4);
    struct edge e1;
    graph_add_edge(&g, &e1, &v1, &v2);
    struct edge e2;
    graph_add_edge(&g, &e2, &v2, &v1);
    struct edge e3;
    graph_add_edge(&g, &e3, &v3, &v1);
    struct edge e4;
    graph_add_edge(&g, &e4, &v1, &v2);
    struct edge e5;
    graph_add_edge(&g, &e5, &v2, &v4);

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

    struct edge e6;
    graph_add_edge(&g, &e6, &v2, &v3);
    struct edge e7;
    graph_add_edge(&g, &e7, &v4, &v3);
    oj_assert(graph_edge_between(&g, &v2, &v3) != NULL, "");
    oj_assert(graph_edge_between(&g, &v4, &v3) != NULL, "");
    oj_assert(graph_edge_between(&g, &v3, &v4) == NULL, "");

    graph_free(&g);
    oj_fresh;
}

oj_test(test_graph_adjacent_vertices) {
    struct graph g = graph_new();
    struct vertex v1;
    graph_add_vertex(&g, &v1);
    struct vertex v2;
    graph_add_vertex(&g, &v2);
    struct vertex v3;
    graph_add_vertex(&g, &v3);
    struct vertex v4;
    graph_add_vertex(&g, &v4);
    struct edge e1;
    graph_add_edge(&g, &e1, &v1, &v2);
    struct edge e2;
    graph_add_edge(&g, &e2, &v2, &v1);
    struct edge e3;
    graph_add_edge(&g, &e3, &v3, &v1);
    struct edge e4;
    graph_add_edge(&g, &e4, &v1, &v2);
    struct edge e5;
    graph_add_edge(&g, &e5, &v2, &v4);

    oj_assert_eq_int(1, graph_vertex_adjacent(&g, &v1, &v2));
    oj_assert_eq_int(1, graph_vertex_adjacent(&g, &v2, &v1));
    oj_assert_eq_int(1, graph_vertex_adjacent(&g, &v3, &v1));
    oj_assert_eq_int(1, graph_vertex_adjacent(&g, &v1, &v3));
    oj_assert_eq_int(0, graph_vertex_adjacent(&g, &v2, &v3));
    oj_assert_eq_int(0, graph_vertex_adjacent(&g, &v4, &v3));
    oj_assert_eq_int(0, graph_vertex_adjacent(&g, &v1, &v4));
    oj_assert_eq_int(1, graph_vertex_adjacent(&g, &v4, &v2));
    oj_assert_eq_int(1, graph_vertex_adjacent(&g, &v2, &v4));

    graph_remove_edge(&g, &v1, &v2);
    oj_assert_eq_int(1, graph_vertex_adjacent(&g, &v1, &v2));
    oj_assert_eq_int(1, graph_vertex_adjacent(&g, &v2, &v1));

    graph_remove_vertex(&g, &v1);
    oj_assert_eq_int(0, graph_vertex_adjacent(&g, &v1, &v2));
    oj_assert_eq_int(0, graph_vertex_adjacent(&g, &v2, &v1));

    struct edge e6;
    graph_add_edge(&g, &e6, &v2, &v3);
    struct edge e7;
    graph_add_edge(&g, &e7, &v4, &v3);
    oj_assert_eq_int(1, graph_vertex_adjacent(&g, &v2, &v3));
    oj_assert_eq_int(1, graph_vertex_adjacent(&g, &v4, &v3));

    graph_free(&g);
    oj_fresh;
}

oj_test(test_graph_degree_queries) {
    struct graph g = graph_new();
    struct vertex v1;
    graph_add_vertex(&g, &v1);
    struct vertex v2;
    graph_add_vertex(&g, &v2);
    struct vertex v3;
    graph_add_vertex(&g, &v3);
    struct vertex v4;
    graph_add_vertex(&g, &v4);
    struct edge e1;
    graph_add_edge(&g, &e1, &v1, &v2);
    struct edge e2;
    graph_add_edge(&g, &e2, &v2, &v1);
    struct edge e3;
    graph_add_edge(&g, &e3, &v3, &v1);
    struct edge e4;
    graph_add_edge(&g, &e4, &v1, &v2);
    struct edge e5;
    graph_add_edge(&g, &e5, &v2, &v4);

    oj_assert_eq_int(1, graph_vertex_out_degree(&v1));
    oj_assert_eq_int(2, graph_vertex_in_degree(&v1));
    oj_assert_eq_int(2, graph_vertex_out_degree(&v2));
    oj_assert_eq_int(1, graph_vertex_in_degree(&v2));
    oj_assert_eq_int(1, graph_vertex_out_degree(&v3));
    oj_assert_eq_int(0, graph_vertex_in_degree(&v3));
    oj_assert_eq_int(0, graph_vertex_out_degree(&v4));
    oj_assert_eq_int(1, graph_vertex_in_degree(&v4));

    graph_remove_vertex(&g, &v1);
    oj_assert_eq_int(1, graph_vertex_out_degree(&v2));
    oj_assert_eq_int(0, graph_vertex_in_degree(&v2));
    oj_assert_eq_int(0, graph_vertex_out_degree(&v3));
    oj_assert_eq_int(0, graph_vertex_in_degree(&v3));

    struct edge e6;
    graph_add_edge(&g, &e6, &v2, &v3);
    struct edge e7;
    graph_add_edge(&g, &e7, &v4, &v3);
    oj_assert_eq_int(2, graph_vertex_out_degree(&v2));
    oj_assert_eq_int(1, graph_vertex_out_degree(&v4));
    oj_assert_eq_int(2, graph_vertex_in_degree(&v3));

    graph_remove_edge(&g, &v2, &v3);
    oj_assert_eq_int(1, graph_vertex_out_degree(&v2));
    oj_assert_eq_int(1, graph_vertex_in_degree(&v3));
    oj_assert_eq_int(1, graph_vertex_in_degree(&v4));

    oj_fresh;
}

oj_test(test_graph_add_vertex_int) {
    struct graph g = graph_new();
    struct vertex_int v = vertex_int_new(&g, 5);
    oj_assert_eq_int(v.value, 5);
    graph_free(&g);
    oj_fresh;
}

oj_test(vertex_int_value_should_return_value_of_vertex_int) {
    struct graph g = graph_new();
    struct vertex_int v = vertex_int_new(&g, 42);
    int result = vertex_int_value(&v.v);
    oj_assert_eq_int(42, result);

    graph_free(&g);
    oj_fresh;
}

oj_test(test_graph_add_weighted_edge) {
    struct graph g = graph_new();
    struct vertex_int v1 = vertex_int_new(&g, 5);
    struct vertex_int v2 = vertex_int_new(&g, 42);
    struct weighted_edge e = weighted_edge_new(&g, 6, &v1.v, &v2.v);
    oj_assert_eq_int(5, vertex_int_value(e.edge.from));
    oj_assert_eq_int(42, vertex_int_value(e.edge.to));
    oj_assert_eq_int(6, e.weight);
    graph_free(&g);
    oj_fresh;
}

oj_test(weighted_edge_weight_should_return_weight_of_edge) {
    struct graph g = graph_new();
    struct vertex_int v1 = vertex_int_new(&g, 5);
    struct vertex_int v2 = vertex_int_new(&g, 42);
    struct weighted_edge e = weighted_edge_new(&g, 100, &v1.v, &v2.v);
    oj_assert_eq_int(100, weighted_edge_weight(&e.edge));
    graph_free(&g);
    oj_fresh;
}

oj_prepare(graph_general_tests) {
    oj_run(test_graph_add_vertex_int);
    oj_run(vertex_int_value_should_return_value_of_vertex_int);
    oj_run(test_graph_add_weighted_edge);
    oj_run(weighted_edge_weight_should_return_weight_of_edge);
    oj_report;
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
    oj_run(test_graph_edge_between);
    oj_run(test_graph_adjacent_vertices);
    oj_run(test_graph_degree_queries);
    oj_report;
    oj_fresh;
}


int main() {
    oj_blend(graph_setup_tests, 0);
    oj_blend(graph_query_tests, 0);
    oj_blend(graph_general_tests, 0);
    return 0;
}
