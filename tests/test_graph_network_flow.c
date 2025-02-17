#include "../headers/graph_network_flow.h"
#include "orange_juice.h"
#include "../headers/logging.h"

oj_test(edmonds_karp_returns_7_for_network_with_7_flow) {
    struct graph g = graph_new();
    int v[6] = { 1, 2, 3, 4, 5, 6 };
    for(int i = 0; i < 6; i++) {
        graph_add_vertex(&g, v + i);
    }
    graph_add_edge(&g, v+0, v+1, 5);
    graph_add_edge(&g, v+0, v+3, 4);
    graph_add_edge(&g, v+3, v+1, 3);
    graph_add_edge(&g, v+3, v+4, 1);
    graph_add_edge(&g, v+1, v+2, 6);
    graph_add_edge(&g, v+2, v+4, 8);
    graph_add_edge(&g, v+2, v+5, 5);
    graph_add_edge(&g, v+4, v+5, 2);

    vector(struct edge*) min_cut = vec_new(struct edge*);
    int result = graph_min_cut(&g, v+0, v+5, min_cut);


    oj_assert_eq_int(2, vec_len(min_cut));

    struct edge* e1 = vec_get(min_cut, 0);
    struct edge* e2 = vec_get(min_cut, 1);

    oj_assert_eq_int(4, *(int*)e1->from);
    oj_assert_eq_int(5, *(int*)e1->to);
    oj_assert_eq_int(2, *(int*)e2->from);
    oj_assert_eq_int(3, *(int*)e2->to);

    oj_assert_eq_int(7, result);

    graph_free(&g);

    oj_fresh;
}

oj_test(edmonds_karp_returns_19_for_network_with_19_flow) {
    struct graph g = graph_new();
    int v[6] = { 1, 2, 3, 4, 5, 6 };
    for(int i = 0; i < 6; i++) {
        graph_add_vertex(&g, v + i);
    }
    graph_add_edge(&g, v+0, v+1, 10);
    graph_add_edge(&g, v+0, v+2, 10);
    graph_add_edge(&g, v+1, v+2, 2);
    graph_add_edge(&g, v+1, v+3, 4);
    graph_add_edge(&g, v+1, v+4, 8);
    graph_add_edge(&g, v+2, v+4, 9);
    graph_add_edge(&g, v+3, v+5, 10);
    graph_add_edge(&g, v+4, v+3, 6);
    graph_add_edge(&g, v+4, v+5, 10);

    int result = graph_max_flow(&g, v+0, v+5);

    oj_assert_eq_int(19, result);

    graph_free(&g);

    oj_fresh;
}

oj_test(edmonds_karp_returns_5_for_network_with_5_flow) {
    struct graph graph = graph_new();

    int a = 'A';
    int b = 'B';
    int c = 'C';
    int d = 'D';
    int e = 'E';
    int f = 'F';
    int g = 'G';

    graph_add_vertex(&graph, &a);
    graph_add_vertex(&graph, &b);
    graph_add_vertex(&graph, &c);
    graph_add_vertex(&graph, &d);
    graph_add_vertex(&graph, &e);
    graph_add_vertex(&graph, &f);
    graph_add_vertex(&graph, &g);

    graph_add_edge(&graph, &a, &b, 3);
    graph_add_edge(&graph, &a, &d, 3);
    graph_add_edge(&graph, &b, &c, 4);
    graph_add_edge(&graph, &c, &a, 3);
    graph_add_edge(&graph, &c, &d, 1);
    graph_add_edge(&graph, &c, &e, 2);
    graph_add_edge(&graph, &d, &e, 2);
    graph_add_edge(&graph, &d, &f, 6);
    graph_add_edge(&graph, &e, &b, 1);
    graph_add_edge(&graph, &e, &g, 1);
    graph_add_edge(&graph, &f, &g, 9);

    int result = graph_max_flow(&graph, &a, &g);

    vector(vector(void*)) disjoint_paths = vec_new(vector(void*));
    oj_assert_eq_int(2, graph_max_vertex_disjoint_paths(&graph, &a, &g, disjoint_paths));
    oj_assert_eq_int(5, result);

    graph_free(&graph);

    oj_fresh;
}

oj_test(graph_max_bipartite_matchings_returns_maximum_matchings_in_a_bipartite_graph) {
    struct graph g = graph_new();
    int v[8] = { 1, 2, 3, 4, 5, 6, 7, 8 };
    for(int i = 0; i < 8; i++) {
        graph_add_vertex(&g, v + i);
    }
    graph_add_edge(&g, v+0, v+4, 1);
    graph_add_edge(&g, v+4, v+2, 1);
    graph_add_edge(&g, v+1, v+6, 1);
    graph_add_edge(&g, v+3, v+6, 1);
    graph_add_edge(&g, v+2, v+5, 1);
    graph_add_edge(&g, v+2, v+7, 1);

    vector(struct edge*) matching = vec_new(struct edge*);
    vector(void*) min_vertex_cover = vec_new(void*);
    int result = graph_max_bipartite_matchings(&g, matching, min_vertex_cover);
    log_array(vec_as_array(matching), struct edge*, 3, x, printf("(%d, %d)", *(int*)x->from, *(int*)x->to));
    log_array(vec_as_array(min_vertex_cover), void*, 3, x, printf("%d", *(int*)x));


    oj_assert_eq_int(3, result);
    oj_fresh;
}

oj_prepare(test_applications_of_network_flow) {
    oj_run(graph_max_bipartite_matchings_returns_maximum_matchings_in_a_bipartite_graph);
    oj_report;
    oj_fresh;
}

oj_prepare(test_edmonds_karp) {
    oj_run(edmonds_karp_returns_19_for_network_with_19_flow);
    oj_run(edmonds_karp_returns_7_for_network_with_7_flow);
    oj_run(edmonds_karp_returns_5_for_network_with_5_flow);
    oj_report;
    oj_fresh;
}

int main() {
    oj_blend(test_edmonds_karp, 0);
    oj_blend(test_applications_of_network_flow, 0);
    return 0;
}
