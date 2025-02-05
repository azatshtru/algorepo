#include "../headers/graph_shortest_path.h"

unsigned int graph_dijkstra(struct graph* graph, void* s, void* e) {
    int vertex_len = graph_vertices_len(graph);
    int distance[vertex_len];
    int processed[vertex_len];
    struct vertex vertices[vertex_len];
    graph_vertices(graph, vertices);


    PriorityQueue(struct vertex) q = priority_queue_new(struct vertex);

    for(int i = 0; i < vertex_len; i++) { 
        distance[i] = INT32_MAX;
        processed[i] = 0;
        if(vertices[i].value == s) {
            distance[i] = 0;
            priority_queue_nq(q, vertices[i], 0);
        }
    }

    while(priority_queue_len(q)) {
        if(processed[index]) { continue; }
        processed[index] = 1;
        struct vertex current = priority_queue_dq(q);
        struct vertex* current = graph_vertex_from_i(graph, index);
        for(int i = 0; i < graph_vertex_out_degree(current); i++) {
            struct vertex* neighbour = vec_get(current->out, i);
            int weight = weighted_edge_weight(graph_edge_between(graph, current, neighbour));
            if(distance[index]+weight < distance[neighbour->i]) {
                distance[neighbour->i] = distance[index]+weight;
                priority_queue_nq(q, neighbour->i, -distance[neighbour->i]);
            }
        }
    }

    return distance[e];
}

unsigned int graph_bellman_ford(struct graph* graph, unsigned int s, unsigned int e) {
    int vertex_len = graph_vertices_len(graph);
    int distance[vertex_len+1];
    for(int i = 1; i <= vertex_len; i++) {
        distance[i] = INT32_MAX;
    }
    distance[s] = 0;

    // This is because the order in which iteration happens might not always be from max to least
    // unless the edges are sorted in reverse order according to their weights
    for(int i = 1; i <= vertex_len-1; i++) {
        int j = -1;
        while((j = hashset_lazy_iterate(graph->edges, j)) != -1) {
            struct edge* edge = (*graph->edges)[j];
            int a = edge->from->i;
            int b = edge->to->i;
            int w = weighted_edge_weight(edge);
            distance[b] = distance[b] < distance[a]+w ? distance[b] : distance[a]+w;
        }
    }

    return distance[e];
}

