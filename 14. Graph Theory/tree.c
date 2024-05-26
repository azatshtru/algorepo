#include "graph.c"

//A tree is a graph that has n nodes and n - 1 edges, ... 
//each node has atmost 1 parent and there exist only unique paths between any two nodes.

void tree_dfs(GraphNode* current_node, GraphNode* prev_node, void (*callback)(GraphNode* s)) {
    callback(current_node);
    for(int i = 0; i < vec_len(current_node->neighbour_list); i++) {
        GraphNode* neighbour = current_node->neighbour_list[i].node;
        if(neighbour != prev_node) {
            tree_dfs(neighbour, current_node, callback);
        }
    }
}

void _tree_children_node_count(GraphNode* current_node, GraphNode* prev_node, uint8* count) {
    count[current_node->graph_index] = 1;
    for(int i = 0; i < vec_len(current_node->neighbour_list); i++) {
        GraphNode* neighbour = current_node->neighbour_list[i].node;
        if(neighbour == prev_node) { continue; }
        _tree_children_node_count(neighbour, current_node, count);
        count[current_node->graph_index] += count[neighbour->graph_index];
    }
}

uint8 tree_children_node_count(GraphNode* root_node, GraphNode* query_node, uint8 number_of_nodes) {
    uint8 count[number_of_nodes];
    _tree_children_node_count(root_node, NULL, count);
    return count[query_node->graph_index];
}