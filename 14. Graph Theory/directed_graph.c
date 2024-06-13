#include "graph.c"
#include "../VI. Queues/circular_deque.c"

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

uint8 xdfs(AdjacencyListGraph adj_graph, uint8 base_node, uint8 current_node, uint8* paths, uint8* visited) {
    if(visited[current_node]) { return paths[current_node]; }
    visited[current_node] = 1;
    if(current_node == base_node) { return 1; }
    uint8 pathsum = 0;
    for(int i = 0; i < vec_len(adj_graph[current_node].neighbour_list); i++) {
        GraphNode u = *(adj_graph[current_node].neighbour_list[i].node);
        pathsum += xdfs(adj_graph, base_node, u.graph_index, paths, visited);
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

    xdfs(adj_graph, query_node_index, starting_node_index, paths, visited);

    return paths[starting_node_index];
}

#endif
