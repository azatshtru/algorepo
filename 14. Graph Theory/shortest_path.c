#include "graph.c"
#include "../VI. Queues/circular_deque.c"

#ifndef GRAPH_SHORTEST_PATH
#define GRAPH_SHORTEST_PATH

#define INFINITY_8BIT 127

int8 min_2(int8 a, int8 b) { return a < b ? a : b; }

//O(nm)
uint8 graph_bellman_ford(EdgeListGraph graph, uint8 starting_node_index, uint8 destination_node_index, uint8 number_of_nodes) {
    int8 distance[number_of_nodes+1];
    for(int i = 1; i <= number_of_nodes; i++) { distance[i] = INFINITY_8BIT; }
    distance[starting_node_index] = 0;

    for(uint8 i = 1; i <= number_of_nodes-1; i++) { //This is because the order in which iteration happens might not always be from max to least unless the edges are sorted in reverse order according to their weights
       for(uint8 e = 0; e < vec_len(graph); e++) {
            int8 a = graph[e].node_a->graph_index;
            int8 b = graph[e].node_b->graph_index;
            int8 w = graph[e].weight;
            distance[b] = min_2(distance[b], distance[a]+w);
        }
    }

    return distance[destination_node_index];
}

//TODO: implement SPFA algorithm
uint8 graph_spfa(AdjacencyListGraph graph, uint8 starting_node_index, uint8 destination_node_index);

//uint8 graph_dijkstra()

#endif