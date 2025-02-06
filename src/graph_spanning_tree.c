#include "../headers/graph_spanning_tree.h"

void graph_kruskal(struct graph* graph, struct graph* minimum_spanning_tree) {
    unsigned int vertex_len = graph_vertices_len(graph);
    unsigned int edges_len = graph_edges_len(graph);
    struct edge edges[edges_len];
    graph_edges(graph, edges);
    quicksort(edges, sizeof(struct edge), 0, edges_len - 1, graph_cmp_edge_by_weight);

    DisjointSetInt forest = disjoint_set_int_new(vertex_len);

    for(int i = 0; i < edges_len; i++) {
        struct vertex from = graph_vertex(graph, edges[i].from);
        struct vertex to = graph_vertex(graph, edges[i].to);
        disjoint_set_int_insert(&forest, from.i);
        disjoint_set_int_insert(&forest, to.i);
        if(disjoint_set_int_union(&forest, from.i, to.i)) {
            graph_add_vertex(minimum_spanning_tree, from.value); 
            graph_add_vertex(minimum_spanning_tree, to.value); 
            graph_add_edge(minimum_spanning_tree, from.value, to.value, edges[i].weight);
        }

    }

    disjoint_set_int_free(&forest);
}

void graph_prim(struct graph* graph, struct graph* spanning_tree) {
    PriorityQueue(struct edge) q = priority_queue_new(struct edge);
    unsigned int vertex_len = graph_vertices_len(graph);
    int processed[vertex_len];
    memzero(processed, vertex_len * sizeof(int));

    for(int i = 0; i < vertex_len; i++) {
        graph_add_vertex(spanning_tree, vec_get(graph->vertices, i));
    }

    void* start = vec_get(graph->vertices, 0);
    for(int i = 0; i < graph_vertex_out_degree(graph, start); i++) {
        void* neighbour = vec_get(graph_vertex(graph, start).out, i);
        struct edge edge = graph_edge_between(graph, start, neighbour);
        priority_queue_nq(q, edge, edge.weight);
    }
    processed[graph_vertex(graph, start).i] = 1;
    int processed_count = 1;

    while(1) {
        struct edge current = priority_queue_dq(q);
        struct vertex to_vertex = graph_vertex(graph, current.to);
        if(processed[to_vertex.i]) continue;
        processed[to_vertex.i] = 1;
        processed_count++;

        if(processed_count == graph_vertices_len(graph)) break;

        graph_add_edge(spanning_tree, current.from, current.to, current.weight);
        for(int i = 0; i < vec_len(to_vertex.out); i++) {
            void* neighbour = vec_get(to_vertex.out, i);
            struct edge edge = graph_edge_between(graph, to_vertex.value, neighbour);
            priority_queue_nq(q, edge, edge.weight);
        }
        
    }
}
