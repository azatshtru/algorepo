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

    NetworkFlowPaths paths;
    network_flow_paths_init(&paths);
    oj_assert_eq_int(2, graph_max_vertex_disjoint_paths(&graph, &a, &g, paths));
    network_flow_paths_free(paths);

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

oj_test(graph_edge_disjoint_paths_returns_edge_disjoint_paths) {
    struct graph g = graph_new();
    int v[6] = { 1, 2, 3, 4, 5, 6 };
    for(int i = 0; i < 6; i++) {
        graph_add_vertex(&g, v + i);
    }
    graph_add_edge(&g, v+0, v+1, 1);
    graph_add_edge(&g, v+0, v+3, 1);
    graph_add_edge(&g, v+1, v+3, 1);
    graph_add_edge(&g, v+2, v+1, 1);
    graph_add_edge(&g, v+2, v+4, 1);
    graph_add_edge(&g, v+2, v+5, 1);
    graph_add_edge(&g, v+3, v+2, 1);
    graph_add_edge(&g, v+3, v+4, 1);
    graph_add_edge(&g, v+4, v+5, 1);
    NetworkFlowPaths paths;
    network_flow_paths_init(&paths);
    int max_edge_disjoint_paths = graph_max_edge_disjoint_paths(&g, v+0, v+5, paths);
    oj_assert_eq_int(2, max_edge_disjoint_paths);

    oj_assert_eq_int(1, graph_path_exists_between(&g, v+0, v+5));
    oj_assert_eq_int(0, graph_path_exists_between(&g, v+1, v+0));

    network_flow_paths_free(paths);

    oj_fresh;
}

oj_test(graph_minimum_node_disjoint_path_covers_returns_minimum_node_disjoint_path_covers) {
    struct graph g = graph_new();
    int v[7] = { 1, 2, 3, 4, 5, 6, 7 };
    for(int i = 0; i < 7; i++) {
        graph_add_vertex(&g, v + i);
    }
    graph_add_edge(&g, v+0, v+4, 1);
    graph_add_edge(&g, v+1, v+5, 1);
    graph_add_edge(&g, v+4, v+5, 1);
    graph_add_edge(&g, v+5, v+6, 1);
    graph_add_edge(&g, v+5, v+2, 1);
    graph_add_edge(&g, v+2, v+3, 1);
    
    vector(struct edge*) matching = vec_new(struct edge*);
    int result = DAG_minimum_vertex_disjoint_path_cover(&g, matching);
    oj_assert_eq_int(3, result);

    vec_free(matching, NULL);
    graph_free(&g);
    
    oj_fresh;
}

oj_test(graph_minimum_node_general_path_covers_DFS_adds_edge_to_matching_graph_if_path_exists_in_original_graph) {
    struct graph g = graph_new();
    int v[7] = { 1, 2, 3, 4, 5, 6, 7 };
    for(int i = 0; i < 7; i++) {
        graph_add_vertex(&g, v + i);
    }
    graph_add_edge(&g, v+0, v+4, 1);
    graph_add_edge(&g, v+1, v+5, 1);
    graph_add_edge(&g, v+4, v+5, 1);
    graph_add_edge(&g, v+5, v+6, 1);
    graph_add_edge(&g, v+5, v+2, 1);
    graph_add_edge(&g, v+2, v+3, 1);
    
    unsigned int vertex_len = graph_vertices_len(&g);
    struct graph matching_graph = graph_new();
    void* duplicates[vertex_len];
    for(int i = 0; i < vertex_len; i++) {
        duplicates[i] = vec_get(g.vertices, i);
        graph_add_vertex(&matching_graph, duplicates[i]);
        graph_add_vertex(&matching_graph, duplicates+i);
    }
    vector(void*) prefix = vec_new(void*);
    int visited[vertex_len];
    memzero(visited, sizeof(int) * vertex_len);
    for(int i = 0; i < vertex_len; i++) {
        DAG_minimum_vertex_general_path_cover_DFS(&g, &matching_graph, duplicates, prefix, v+i, visited);
    }

    struct edge* edges[graph_edges_len(&matching_graph)];
    graph_edges(&matching_graph, edges);
    vec_free(prefix, NULL);

    // log_array(edges, struct edge*, graph_edges_len(&matching_graph), e, printf("(%d, %d)", *(int*)e->from, **(int**)e->to));

    oj_assert_eq_int(17, graph_edges_len(&matching_graph));
    oj_assert_eq_int(5, vec_len(graph_vertex(&matching_graph, v+0)->out));
    oj_assert_eq_int(4, vec_len(graph_vertex(&matching_graph, v+1)->out));
    oj_assert_eq_int(1, vec_len(graph_vertex(&matching_graph, v+2)->out));
    oj_assert_eq_int(0, vec_len(graph_vertex(&matching_graph, v+3)->out));
    oj_assert_eq_int(4, vec_len(graph_vertex(&matching_graph, v+4)->out));
    oj_assert_eq_int(3, vec_len(graph_vertex(&matching_graph, v+5)->out));
    oj_assert_eq_int(0, vec_len(graph_vertex(&matching_graph, v+6)->out));

    graph_free(&g);
    oj_fresh;
}

oj_test(graph_minimum_node_general_path_covers_returns_minimum_node_general_path_covers) {
    struct graph g = graph_new();
    int v[7] = { 1, 2, 3, 4, 5, 6, 7 };
    for(int i = 0; i < 7; i++) {
        graph_add_vertex(&g, v + i);
    }
    graph_add_edge(&g, v+0, v+4, 1);
    graph_add_edge(&g, v+1, v+5, 1);
    graph_add_edge(&g, v+4, v+5, 1);
    graph_add_edge(&g, v+5, v+6, 1);
    graph_add_edge(&g, v+5, v+2, 1);
    graph_add_edge(&g, v+2, v+3, 1);

    vector(struct edge) path_cover = vec_new(struct edge);
    int result = DAG_minimum_vertex_general_path_cover(&g, path_cover);

    // log_array(vec_as_array(path_cover), struct edge, vec_len(path_cover), x, printf("(%d, %d)", *(int*)x.from, *(int*)x.to));

    oj_assert_eq_int(5, vec_len(path_cover));
    oj_assert_eq_int(2, result);


    vec_free(path_cover, NULL);
    graph_free(&g);
    oj_fresh;
}

oj_prepare(test_applications_of_network_flow) {
    oj_run(graph_max_bipartite_matchings_returns_maximum_matchings_in_a_bipartite_graph);
    oj_run(graph_edge_disjoint_paths_returns_edge_disjoint_paths);
    oj_run(graph_minimum_node_disjoint_path_covers_returns_minimum_node_disjoint_path_covers);
    oj_run(graph_minimum_node_general_path_covers_DFS_adds_edge_to_matching_graph_if_path_exists_in_original_graph);
    oj_run(graph_minimum_node_general_path_covers_returns_minimum_node_general_path_covers);
    oj_report;
    oj_fresh;
}

oj_prepare(test_edmonds_karp) {
    oj_run(edmonds_karp_returns_7_for_network_with_7_flow);
    oj_run(edmonds_karp_returns_19_for_network_with_19_flow);
    oj_run(edmonds_karp_returns_5_for_network_with_5_flow);
    oj_report;
    oj_fresh;
}

int main() {
    oj_blend(test_edmonds_karp, 0);
    oj_blend(test_applications_of_network_flow, 0);
    return 0;
}
