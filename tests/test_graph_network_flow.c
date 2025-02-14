#include "../headers/graph_network_flow.h"
#include "orange_juice.h"
#include "../headers/logging.h"

oj_test(edmonds_karp_returns_7_for_network_with_7_flow) {
    struct graph* g = graph_new();
    int things[6] = { 1, 2, 3, 4, 5, 6 };
    struct vertex* v[6];
    for(int i = 0; i < 6; i++) {
        v[i] = graph_add_vertex(g, things + i);
    }
    graph_add_edge(g, v[0], v[1], 5);
    graph_add_edge(g, v[0], v[3], 4);
    graph_add_edge(g, v[3], v[1], 3);
    graph_add_edge(g, v[3], v[4], 1);
    graph_add_edge(g, v[1], v[2], 6);
    graph_add_edge(g, v[2], v[4], 8);
    graph_add_edge(g, v[2], v[5], 5);
    graph_add_edge(g, v[4], v[5], 2);

    vector(struct edge*) min_cut = vec_new(struct edge*);
    int result = graph_min_cut(g, v[0], v[5], min_cut);

    struct edge* e1 = vec_get(min_cut, 0);
    struct edge* e2 = vec_get(min_cut, 1);

    oj_assert_eq_int(7, result);

    oj_assert_eq_int(4, *(int*)e1->from->value);
    oj_assert_eq_int(5, *(int*)e1->to->value);
    oj_assert_eq_int(2, *(int*)e2->from->value);
    oj_assert_eq_int(3, *(int*)e2->to->value);

    graph_free(g);
    vec_free(min_cut, NULL);

    oj_fresh;
}

oj_test(edmonds_karp_returns_19_for_network_with_19_flow) {
    struct graph* g = graph_new();
    int things[6] = { 1, 2, 3, 4, 5, 6 };
    struct vertex* v[6];
    for(int i = 0; i < 6; i++) {
        v[i] = graph_add_vertex(g, things + i);
    }
    graph_add_edge(g, v[0], v[1], 10);
    graph_add_edge(g, v[0], v[2], 10);
    graph_add_edge(g, v[1], v[2], 2);
    graph_add_edge(g, v[1], v[3], 4);
    graph_add_edge(g, v[1], v[4], 8);
    graph_add_edge(g, v[2], v[4], 9);
    graph_add_edge(g, v[3], v[5], 10);
    graph_add_edge(g, v[4], v[3], 6);
    graph_add_edge(g, v[4], v[5], 10);

    int result = graph_max_flow(g, v[0], v[5]);

    oj_assert_eq_int(19, result);

    graph_free(g);

    oj_fresh;
}

oj_test(edmonds_karp_returns_5_for_network_with_5_flow) {
    struct graph* graph = graph_new();
    char characters[7] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G' };

    struct vertex* a = graph_add_vertex(graph, characters + 0);
    struct vertex* b = graph_add_vertex(graph, characters + 1);
    struct vertex* c = graph_add_vertex(graph, characters + 2);
    struct vertex* d = graph_add_vertex(graph, characters + 3);
    struct vertex* e = graph_add_vertex(graph, characters + 4);
    struct vertex* f = graph_add_vertex(graph, characters + 5);
    struct vertex* g = graph_add_vertex(graph, characters + 6);

    graph_add_edge(graph, a, b, 3);
    graph_add_edge(graph, a, d, 3);
    graph_add_edge(graph, b, c, 4);
    graph_add_edge(graph, c, a, 3);
    graph_add_edge(graph, c, d, 1);
    graph_add_edge(graph, c, e, 2);
    graph_add_edge(graph, d, e, 2);
    graph_add_edge(graph, d, f, 6);
    graph_add_edge(graph, e, b, 1);
    graph_add_edge(graph, e, g, 1);
    graph_add_edge(graph, f, g, 9);

    int result = graph_max_flow(graph, a, g);

    oj_assert_eq_int(5, result);

    // oj_assert_eq_int(2, graph_max_node_disjoint_paths(graph, a, g));

    graph_free(graph);

    oj_fresh;
}

oj_prepare(test_edmonds_karp) {
    oj_run(edmonds_karp_returns_5_for_network_with_5_flow);
    oj_run(edmonds_karp_returns_19_for_network_with_19_flow);
    oj_run(edmonds_karp_returns_7_for_network_with_7_flow);
    oj_report;
    oj_fresh;
}

int main() {
    oj_blend(test_edmonds_karp, 0);
    return 0;
}
