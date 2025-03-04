#include "graph.h"
#include "rmq_sparse_table.h"
#include "disjoint_set_int.h"

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

void tree_ancestor_binary_lift_dfs(struct graph* tree, void* current, void* parent, int** ancestor, int* tin, int* tout, int t);
int tree_vertex_is_ancestor(struct graph* tree, void* ancestor, void* descendant, int* tin, int* tout);
void* tree_vertex_ancestor(struct graph* tree, void* current, int** ancestor, int k);
void* tree_lowest_common_ancestor_binary_lift(struct graph* tree, void* u, void* v, void* root);
int tree_dfs_traversal_order(struct graph* tree, void* current, void* parent, int* visited, vector(void*) order, int* subtree_size);
void tree_euler_tour(struct graph* tree, void* current, void* parent, int h, int* depth, int* visited, vector(void*) euler_tour);
void tree_lowest_common_ancestor_farach_colton_and_bender(
    struct graph* tree, void* root,
    int query_len, void** u, void** v, void** out, int* distance
);
void tree_lowest_common_ancestor_offline_dfs(
    struct graph* tree, void* current, void* parent, int depth,
    int* visited, DisjointSetInt* dsu, int* highest, struct graph* lca
);
void tree_lowest_common_ancestor_offline(
    struct graph* tree, void* root,
    int query_len, void** u, void** v, void** out
);

#endif
