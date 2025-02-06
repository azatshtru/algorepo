#include "../headers/graph_shortest_path.h"

unsigned int graph_dijkstra(struct graph* graph, void* s, void* e) {
    int vertex_len = graph_vertices_len(graph);
    int distance[vertex_len];
    int processed[vertex_len];

    PriorityQueue(struct vertex) q = priority_queue_new(struct vertex);

    for(int i = 0; i < vertex_len; i++) { 
        distance[i] = INT32_MAX;
        processed[i] = 0;
    }

    distance[graph_vertex(graph, s).i] = 0;
    priority_queue_nq(q, graph_vertex(graph, s), 0);

    while(priority_queue_len(q)) {
        struct vertex current = priority_queue_dq(q);
        if(processed[current.i]) { continue; }
        processed[current.i] = 1;
        for(int i = 0; i < vec_len(current.out); i++) {
            struct vertex neighbour = graph_vertex(graph, vec_get(current.out, i));
            int weight = graph_edge_weight(graph, current.value, neighbour.value);
            if(distance[current.i] + weight < distance[neighbour.i]) {
                distance[neighbour.i] = distance[current.i] + weight;
                priority_queue_nq(q, neighbour, distance[neighbour.i]);
            }
        }
    }

    return distance[graph_vertex(graph, e).i];
}

unsigned int graph_bellman_ford(struct graph* graph, void* s, void* e) {
    int vertex_len = graph_vertices_len(graph);
    int distance[vertex_len + 1];
    for(int i = 1; i <= vertex_len; i++) {
        distance[i] = INT32_MAX;
    }
    distance[graph_vertex(graph, s).i] = 0;

    struct edge edges[graph_edges_len(graph)];
    graph_edges(graph, edges);

    // This is because the order in which iteration happens might not always be from max to least
    // unless the edges are sorted in reverse order according to their weights
    for(int i = 1; i <= vertex_len - 1; i++) {
        for(int j = 0; j < graph_edges_len(graph); j++) {
            struct edge edge = edges[j];
            int a = graph_vertex(graph, edge.from).i;
            int b = graph_vertex(graph, edge.to).i;
            int w = graph_edge_weight(graph, edge.from, edge.to);
            distance[b] = distance[b] < distance[a] + w ? distance[b] : distance[a] + w;
        }
    }

    return distance[graph_vertex(graph, e).i];
}

