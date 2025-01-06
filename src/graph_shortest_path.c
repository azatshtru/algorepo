#include "../headers/graph_shortest_path.h"

unsigned int graph_dijkstra(struct graph* graph, unsigned int s, unsigned int e) {
    int distance[graph_vertices_len(graph)];
    int processed[graph_vertices_len(graph)];

    PriorityQueue(int) q = priority_queue_new(int, 0);

    for(int i = 0; i < vec_len(graph); i++) { 
        distance[i] = INT32_MAX;
        processed[i] = 0;
    }
    distance[s] = 0;
    priority_queue_nqx(q, 0, 0);

    while(priority_queue_len(q)) {
        int index = priority_queue_dq(q);
        if(processed[index]) { continue; }
        processed[index] = 1;
        struct vertex* current = graph_vertex_by_index(graph, index);
        for(int i = 0; i < graph_vertex_neighbors_len(current); i++) {
            struct vertex* neighbour = vec_get(graph_vertex_neighbors(current), i);
            int weight = weighted_edge_weight(graph_edge_by_from_to(graph, current, neighbour));
            if(distance[index]+weight < distance[neighbour->i]) {
                distance[neighbour->i] = distance[index]+weight;
                priority_queue_nqx(q, neighbour->i, -distance[neighbour->i]);
            }
        }
    }

    return distance[e];
}


