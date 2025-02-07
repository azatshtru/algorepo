#ifndef BINARY_TREE
#define BINARY_TREE

typedef struct binary_tree_node {
    void* data;
    struct binary_tree_node* left;
    struct binary_tree_node* right;
} BinaryTreeNode;

void binary_tree_pre_order_traversal(BinaryTreeNode node, void (*callback)(BinaryTreeNode));
void binary_tree_in_order_traversal(BinaryTreeNode node, void (*callback)(BinaryTreeNode));
void binary_tree_post_order_traversal(BinaryTreeNode node, void (*callback)(BinaryTreeNode));

#endif