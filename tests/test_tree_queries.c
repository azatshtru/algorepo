#include "../headers/tree.h"
#include "orange_juice.h"
#include "../headers/logging.h"

oj_test(test_farach_colton_and_bender_lca_impl) {
    int things[8] = { 1, 2, 3, 4, 5, 6, 7, 8 };
    struct graph g = graph_new();
    for(int i = 0; i < 8; i++) {
        graph_add_vertex(&g, things + i);
    }
    graph_add_edge_symmetric(&g, things + 0, things + 1, 1);
    graph_add_edge_symmetric(&g, things + 0, things + 2, 1);
    graph_add_edge_symmetric(&g, things + 0, things + 3, 1);
    graph_add_edge_symmetric(&g, things + 1, things + 4, 1);
    graph_add_edge_symmetric(&g, things + 1, things + 5, 1);
    graph_add_edge_symmetric(&g, things + 3, things + 6, 1);
    graph_add_edge_symmetric(&g, things + 5, things + 7, 1);

    int depth[8] = { 0 };
    int visited[8] = { 0 };
    vector(void*) euler_tour = vec_new(void*);
    tree_euler_tour(&g, things + 0, things + 0, 1, depth, visited, euler_tour);

    void* u[3] = { things + 4, things + 3, things + 5 };
    void* v[3] = { things + 7, things + 7, things + 2 };
    void* out[3];

    tree_lowest_common_ancestor_farach_colton_and_bender(&g, things + 0, 3, u, v, out);

    oj_assert_eq_int(2, *(int*)out[0]);
    oj_assert_eq_int(1, *(int*)out[1]);
    oj_assert_eq_int(1, *(int*)out[2]);

    oj_fresh;
}

oj_prepare(test_lowest_common_ancestor) {
    oj_run(test_farach_colton_and_bender_lca_impl);
    oj_report;
    oj_fresh;
}

int main() {
    oj_blend(test_lowest_common_ancestor, 0);
    return 0;
}
