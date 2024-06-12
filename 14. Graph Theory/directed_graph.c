#include "graph.c"

#ifndef ACYCLIC_GRAPH
#define ACYCLIC_GRAPH

boolean acyclic_graph_dfs(GraphNode* node, uint8* state, uint8** topological_order) {
    if(state[node->graph_index] == 2) { return TRUE; }
    if(state[node->graph_index] == 1) { return FALSE; }
    boolean flag;
    state[node->graph_index] = 1;
    for(int i = 0; i < vec_len(node->neighbour_list); i++) {
        GraphNode* u = node->neighbour_list[i].node;
        flag = acyclic_graph_dfs(u, state, topological_order);
        if(flag == FALSE) { break; }
    }
    state[node->graph_index] = 2;
    __vec_push__(*topological_order, node->graph_index);
    return flag;
}

uint8* acyclic_graph_sort_topologically(AdjacencyListGraph adj_graph) {
    uint8 state[vec_len(adj_graph)];
    for(int i = 0; i < vec_len(adj_graph); i++) { state[i] = 0; }
    uint8* topological_order = __vec_new__(uint8);
    for(int i = 0; i < vec_len(adj_graph); i++) {
        if(state[i]!=0) { continue; }
        acyclic_graph_dfs(adj_graph+i, state, &topological_order); 
    }
    for(int i = 0, j = vec_len(adj_graph)-1; i < j; i++, j--) {
        topological_order[i] = topological_order[i] ^ topological_order[j];
        topological_order[j] = topological_order[i] ^ topological_order[j];
        topological_order[i] = topological_order[i] ^ topological_order[j];
    }
    return topological_order;
}

#endif
