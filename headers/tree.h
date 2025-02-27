#include "graph.h"
#include "rmq_sparse_table.h"

#ifndef TREE
#define TREE

int graph_is_tree(struct graph* graph, void** parent);
void tree_subtree_size(struct graph* graph, void* current, void* prev, int* size);
void tree_parent(struct graph* tree, void* current, void* prev, void** parent);
void tree_furthest_leaf_distance(
    struct graph* graph,
    void* current, 
    int* primary_distance,
    int* visited,
    void* prev,
    int* secondary_distance,
    void** next
);
int tree_longest_path_from_vertex(struct graph* graph, void* query);
int tree_longest_path_through_vertex(struct graph* graph, void* query);
void tree_all_longest_paths(struct graph* tree, int* longest_path);
int tree_diameter(struct graph* tree);

int graph_is_binary_tree(struct graph* graph);


#endif
