#include "../headers/graph.h"

/// pre-order: first process the root, then traverse the left subtree, then traverse the right subtree
void binary_tree_pre_order_traverse(struct graph* tree);

/// in-order: first traverse the left subtree, then process the root, then traverse the right subtree
void binary_tree_in_order_traverse(struct graph* tree);

/// post-order: first traverse the left subtree, then traverse the right subtree, then process the root
void binary_tree_post_order_traverse(struct graph* tree);

int main() {
    return 0;
}
