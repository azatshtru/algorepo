#include "../VI. Queues/circular_deque.c"
#include "graph_traversal.c"

//A tree is a graph that has n nodes and n - 1 edges, ... 
//each node has atmost 1 parent and there exist only unique paths between any two nodes.

boolean graph_is_tree(AdjacencyListGraph graph) {
    return !graph_cycle_check(graph, NULL, 0);
}

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

void tree_parent_nodes(GraphNode* node, GraphNode* prev_node, uint8* parent_node) {
    for(int i = 0; i < vec_len(node->neighbour_list); i++) {
        GraphNode* u = node->neighbour_list[i].node;
        if(u != prev_node) {
            parent_node[u->graph_index] = node->graph_index;
            tree_parent_nodes(u, node, parent_node);
        }
    }
}

void tree_furthest_leaf_distance(
    GraphNode* node, 
    int32* distance,
    boolean* visited,
    GraphNode* prev_node,
    int32* alter_distance,
    uint8* max_next_node) 
{
    if(visited[node->graph_index]) { return; }
    visited[node->graph_index] = TRUE;
    int32 max = 0;
    int32 altmax = 0;
    uint8 max_index = 0;

    for(int i = 0; i < vec_len(node->neighbour_list); i++) {
        GraphNode* u = node->neighbour_list[i].node;
        int32 weight = node->neighbour_list[i].weight;

        if(u == prev_node) { continue; }

        tree_furthest_leaf_distance(u, distance, visited, node, alter_distance, max_next_node);
        if(distance[u->graph_index]+weight >= max) {
            altmax = max;
            max = distance[u->graph_index]+weight;
            max_index = u->graph_index;
            continue;
        }
        if(distance[u->graph_index]+weight >= altmax) {
            altmax = distance[u->graph_index]+weight;
        }
    }
    distance[node->graph_index] = max;
    if(alter_distance != NULL) { alter_distance[node->graph_index] = altmax; }
    if(max_next_node != NULL) { max_next_node[node->graph_index] = max_index; }
}

uint8 tree_longest_path_from_node(GraphNode* query_node, uint8 tree_size) {
    int32* distance = (int32*)malloc(sizeof(int32)*tree_size);
    boolean* visited = (boolean*)malloc(sizeof(boolean)*tree_size);

    tree_furthest_leaf_distance(query_node, distance, visited, NULL, NULL, NULL);
    int32 query_distance = distance[query_node->graph_index];

    free(distance);
    free(visited);

    return query_distance;
}

uint8 tree_longest_path_through_node(GraphNode* query_node, uint8 tree_size) {
    int32* distance = (int32*)malloc(sizeof(int32)*tree_size);
    int32* alter_distance = (int32*)malloc(sizeof(int32)*tree_size);
    boolean* visited = (boolean*)malloc(sizeof(boolean)*tree_size);

    tree_furthest_leaf_distance(query_node, distance, visited, NULL, alter_distance, NULL);
    int32 max_1 = distance[query_node->graph_index];
    int32 max_2 = alter_distance[query_node->graph_index];

    free(distance);
    free(visited);
    free(alter_distance);

    return max_1+max_2;
}

void tree_all_longest_paths(AdjacencyListGraph tree, int32* longest_path) {
    uint8 tree_size = vec_len(tree);
    int32* distance = (int32*)malloc(sizeof(int32)*tree_size);
    int32* alter_distance = (int32*)malloc(sizeof(int32)*tree_size);
    boolean* visited = (boolean*)malloc(sizeof(boolean)*tree_size);
    uint8* max_next_node = (uint8*)malloc(sizeof(uint8)*tree_size);
    uint8* parent_node = (uint8*)malloc(sizeof(uint8)*tree_size);

    tree_furthest_leaf_distance(tree, distance, visited, NULL, alter_distance, max_next_node);
    tree_parent_nodes(tree, NULL, parent_node);

    for(int i = 1; i < tree_size; i++) {
        if(max_next_node[parent_node[i]] == i && alter_distance[parent_node[i]] + 1 > distance[i]) { 
            alter_distance[i] = distance[i];
            distance[i] = alter_distance[parent_node[i]] + 1;
            max_next_node[i] = parent_node[i];
        } else if(max_next_node[parent_node[i]] != i && distance[parent_node[i]] + 1 > distance[i]) {
            alter_distance[i] = distance[i];
            distance[i] = distance[parent_node[i]] + 1;
            max_next_node[i] = parent_node[i];
        }
    }

    for(uint8 i = 0; i < tree_size; i++) { longest_path[i] = distance[i]; }

    free(distance);
    free(visited);
    free(alter_distance);
    free(max_next_node);
    free(parent_node);
} 

uint8 tree_diameter(AdjacencyListGraph tree) {
    uint8 tree_size = vec_len(tree);
    int32* distance = (int32*)malloc(sizeof(int32)*tree_size);
    boolean* visited = (boolean*)malloc(sizeof(boolean)*tree_size);
    uint8* max_next_node = (uint8*)malloc(sizeof(uint8)*tree_size);

    tree_furthest_leaf_distance(tree, distance, visited, NULL, NULL, max_next_node);
    int i = 0;
    while(max_next_node[i] != 0) { i = max_next_node[i]; }

    memset(distance, 0, tree_size*sizeof(int32));
    memset(visited, 0, tree_size*sizeof(boolean));
    memset(max_next_node, 0, tree_size*sizeof(boolean));

    tree_furthest_leaf_distance(tree+i, distance, visited, NULL, NULL, max_next_node);
    int32 diameter = distance[i];

    free(distance);
    free(visited);
    free(max_next_node);

    return diameter;
}