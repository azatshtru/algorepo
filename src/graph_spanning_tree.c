#include "../headers/graph_spanning_tree.h"

void graph_kruskal(struct graph* graph, struct graph* minimum_spanning_tree) {
    struct edge* edges[graph_edges_len(graph)];
    graph_edges(graph, edges);
    quicksort(vec_as_array(edges), sizeof(struct edge*), 0, vec_len(edges)-1, graph_weighted_edge_cmp);

    unsigned int vertex_len = graph_vertices_len(graph);

    DisjointSetInt forest = disjoint_set_int_new(vertex_len);

    for(int i = 0; i < vec_len(edges); i++) {
        struct vertex* from = edges[i]->from;
        struct vertex* to = edges[i]->to;
        disjoint_set_int_insert(&forest, from->i);
        disjoint_set_int_insert(&forest, to->i);
        if(disjoint_set_int_union(&forest, from->i, to->i)) {
            graph_add_vertex(minimum_spanning_tree, from); 
            graph_add_vertex(minimum_spanning_tree, to); 
            graph_add_edge(minimum_spanning_tree, edges[i], from, to);
        }

    }

    disjoint_set_int_free(&forest);
}

void graph_prim(struct graph* graph, struct graph* spanning_tree) {
    PriorityQueue(struct vertex*) q = priority_queue_new(struct vertex*);
    struct edge* edges[graph_edges_len(graph)];

    unsigned int vertex_len = graph_vertices_len(graph);
    int processed[vertex_len+1];
    unsigned int distance[vertex_len+1];

    for(int i = 0; i < vertex_len; i++) { 
        distance[i] = I32_MAX;
        processed[i] = 0;
    }

    priority_queue_nq(q, graph_vertex_from_i(graph, 0), 0);

    for(int j = 0; j < vertex_len - 1; j++) {
        struct vertex* s = priority_queue_dq(q);
        if(processed[s->i]) { continue; }
        processed[s->i] = 1;

        graph_add_vertex(spanning_tree, s);
        if(edges[s->i] != NULL) {
            struct edge* edge = edges[s->i];
            graph_add_edge(spanning_tree, edge, edge->from, edge->to);
        }
        
        uint32 n = graph_vertex_out_degree(s);
        for(int i = 0; i < n; i++) {
            struct vertex* u = vec_get(s->out, i);
            struct edge* edge = graph_edge_between(graph, s, u);
            int weight = weighted_edge_weight(edge);
            priority_queue_nq(q, u, -weight);
            if(!processed[u->i] && distance[u->i] > weight) {
                distance[u->i] = weight;
                edges[u->i] = edge;
            }
        }
    }
}
