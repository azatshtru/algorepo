#include "../headers/graph.h"
#include "orange_juice.h"

oj_test(graph_allocates) {
    struct graph g = graph_new();
    oj_assert(g.edges != NULL, "graph edges didn't allocate properly");
    oj_assert(g.vertices != NULL, "graph vertices didn't allocate properly");
    oj_fresh;
}

oj_test(graph_vertex_allocates) {
    struct graph g = graph_new();
    struct vertex* v = graph_add_vertex(&g);
    oj_assert(v != NULL, "vertex didn't allocate properly");
    oj_assert(v->neighbors != NULL, "neighbors vectors didn't allocate properly");
    oj_fresh;
}

oj_prepare(graph_setup_tests) {
    oj_run(graph_allocates);
    oj_run(graph_vertex_allocates);
    oj_report;
    oj_fresh;
}

int main() {
    oj_blend(graph_setup_tests, 0);
    return 0;
}
