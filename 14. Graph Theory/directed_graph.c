#include "graph.c"
#include "../VI. Queues/circular_deque.c"
#include "../VI. Queues/priority_queue.c"

#define INFINITY_8BIT 127778

#ifndef ACYCLIC_GRAPH
#define ACYCLIC_GRAPH

boolean acyclic_graph_topological_dfs(GraphNode* node, uint8* state, uint8** topological_order) {
    if(state[node->graph_index] == 2) { return TRUE; }
    if(state[node->graph_index] == 1) { return FALSE; }
    boolean flag;
    state[node->graph_index] = 1;
    for(int i = 0; i < vec_len(node->neighbour_list); i++) {
        GraphNode* u = node->neighbour_list[i].node;
        flag = acyclic_graph_topological_dfs(u, state, topological_order);
        if(flag == FALSE) { break; }
    }
    state[node->graph_index] = 2;
    if(topological_order != NULL) { __vec_push__(*topological_order, node->graph_index); }
    return flag;
}

uint8* acyclic_graph_sort_topologically(AdjacencyListGraph adj_graph) {
    uint8 state[vec_len(adj_graph)];
    for(int i = 0; i < vec_len(adj_graph); i++) { state[i] = 0; }
    uint8* topological_order = __vec_new__(uint8);
    for(int i = 0; i < vec_len(adj_graph); i++) {
        if(state[i]!=0) { continue; }
        if(acyclic_graph_topological_dfs(adj_graph+i, state, &topological_order)) { continue; }
        else { return NULL; }
    }
    for(int i = 0, j = vec_len(adj_graph)-1; i < j; i++, j--) {
        topological_order[i] = topological_order[i] ^ topological_order[j];
        topological_order[j] = topological_order[i] ^ topological_order[j];
        topological_order[i] = topological_order[i] ^ topological_order[j];
    }
    return topological_order;
}

uint8 _acyclic_graph_number_of_paths(AdjacencyListGraph adj_graph, uint8 base_node, uint8 current_node, uint8* paths, uint8* visited) {
    if(visited[current_node]) { return paths[current_node]; }
    visited[current_node] = 1;
    if(current_node == base_node) { return 1; }
    uint8 pathsum = 0;
    for(int i = 0; i < vec_len(adj_graph[current_node].neighbour_list); i++) {
        GraphNode u = *(adj_graph[current_node].neighbour_list[i].node);
        pathsum += _acyclic_graph_number_of_paths(adj_graph, base_node, u.graph_index, paths, visited);
    }
    paths[current_node] = pathsum;
    return pathsum;
}

uint8 acyclic_graph_number_of_paths(AdjacencyListGraph adj_graph, uint8 starting_node_index, uint8 query_node_index) {
    uint8 paths[vec_len(adj_graph)];
    boolean visited[vec_len(adj_graph)];
    for(int i = 0; i < vec_len(adj_graph); i++) { 
        paths[i] = 0;
        visited[i] = FALSE;
    }
    paths[query_node_index] = 1;

    _acyclic_graph_number_of_paths(adj_graph, query_node_index, starting_node_index, paths, visited);

    return paths[starting_node_index];
}

void graph_dijkstra_acyclic_product(AdjacencyListGraph graph, uint8 starting_node_index, AdjacencyListGraph* acyclic_graph) {
    int32 distance[vec_len(graph)];
    boolean processed[vec_len(graph)];
    PriorityQueue q = priority_queue_new();
    uint8* prev_path_node[vec_len(graph)];

    for(int i = 0; i < vec_len(graph); i++) { 
        distance[i] = INFINITY_8BIT;
        processed[i] = FALSE;
        prev_path_node[i] = __vec_new__(uint8);
    }
    distance[starting_node_index] = 0;
    priority_queue_nq(q, &starting_node_index, 0);

    while(vec_len(q)) {
        uint8 a = *(uint8*)priority_queue_dq(q);
        if(processed[a]) { continue; }
        processed[a] = TRUE;
        for(uint8 i = 0; i < vec_len(graph[a].neighbour_list); i++) {
            GraphNode* neighbour = graph[a].neighbour_list[i].node;
            int32 w = graph[a].neighbour_list[i].weight;
            if(distance[a]+w < distance[neighbour->graph_index]) {
                distance[neighbour->graph_index] = distance[a]+w;
                priority_queue_nq(q, &neighbour->graph_index, -distance[neighbour->graph_index]);
                vec_clear(prev_path_node[neighbour->graph_index]);
                __vec_push__(prev_path_node[neighbour->graph_index], a);
            }
            if(distance[a]+w == distance[neighbour->graph_index]) {
                __vec_push__(prev_path_node[neighbour->graph_index], a);
            }
        }
    }

    for(int i = 0; i < vec_len(graph); i++) { graph_node_new(*acyclic_graph, graph[i].value); }
    for(int i = 0; i < vec_len(graph); i++) {
        for(int j = 0; j < vec_len(prev_path_node[i]); j++) {
            graph_node_add_neighbours((*acyclic_graph)+prev_path_node[i][j], FALSE, 1, (*acyclic_graph)+i, 1);
        }
    }
    for(int i = 0; i < vec_len(graph); i++) { vec_free(prev_path_node[i], NULL); }
}

#endif
