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
        struct vertex* current = graph_vertex_from_id(graph, index);
        for(int i = 0; i < graph_vertex_out_degree(current); i++) {
            struct vertex* neighbour = vec_get(current->out, i);
            int weight = weighted_edge_weight(graph_edge_between(graph, current, neighbour));
            if(distance[index]+weight < distance[neighbour->i]) {
                distance[neighbour->i] = distance[index]+weight;
                priority_queue_nqx(q, neighbour->i, -distance[neighbour->i]);
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

     //This is because the order in which iteration happens might not always be from max to least unless the edges are sorted in reverse order according to their weights
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

