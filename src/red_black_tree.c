#include "../headers/red_black_tree.h"

RedBlackTreeNode* red_black_tree_node_new(int key) {
    struct red_black_tree_node* node = malloc(sizeof(struct red_black_tree_node));
    node->parent = NULL;
    node->color = RED;
    node->left = NULL;
    node->right = NULL;
    return node;
}

RedBlackTree red_black_tree_new() {
    struct red_black_tree tree;
    tree.nil = red_black_tree_node_new(I32_MAX);
    tree.nil->color = BLACK;
    tree.nil->left = NULL;
    tree.nil->right = NULL;
    tree.root = tree.nil;
    return tree;
}

void red_black_tree_left_rotate(RedBlackTree* tree, RedBlackTreeNode* node) {
    RedBlackTreeNode* right_child = node->right;
    node->right = right_child->left;

    if(right_child->left != tree->nil) {
        right_child->left->parent = node;
    }
    
    right_child->parent = node->parent;

    if(node->parent == NULL) {
        tree->root = right_child;
    } else if(node == node->parent->left) {
        node->parent->left = right_child;
    } else {
        node->parent->right = right_child;
    }

    right_child->left = node;
    node->parent = right_child;
}

void red_black_tree_right_rotate(RedBlackTree* tree, RedBlackTreeNode* node) {
    RedBlackTreeNode* left_child = node->left;
    node->left = left_child->right;

    if(left_child->right != tree->nil) {
        left_child->right->parent = node;
    }

    left_child->parent = node->parent;

    if(node->parent == NULL) {
        tree->root = left_child;
    } else if(node == node->parent->right) {
        node->parent->right = left_child;
    } else {
        node->parent->left = left_child; 
    }

    left_child->right = node;
    node->parent = left_child;
}

void red_black_tree_insert(RedBlackTree* tree, int key) {
    RedBlackTreeNode* node = red_black_tree_node_new(key);
    node->left = tree->nil;
    node->right = tree->nil;

    RedBlackTreeNode* current = NULL; 
    RedBlackTreeNode* root = tree->root;
    
    while(root != tree->nil) {
        current = root;
        if(node->key < root->key) {
            root = root->left;
        } else {
            root = root->right;
        }
    }
    
    node->parent = current; 
    if(current == NULL) {
        tree->root = node;
    } else if(node->key < current->key) {
        current->left = node; 
    } else {
        current->right = node;
    }

    red_black_tree_insert_fixup(tree, node);
}

void red_black_tree_insert_fixup(RedBlackTree* tree, RedBlackTreeNode* node) {
    while(node->parent && node->parent->color == RED) {
        if(node->parent == node->parent->parent->left) {
            RedBlackTreeNode* uncle = node->parent->parent->right;
            if(uncle->color == RED) {
                node->parent->color = BLACK;
                uncle->color = BLACK;
                node->parent->parent->color = RED;
                node = node->parent->parent;
            } else {
                if(node == node->parent->right) {
                    node = node->parent;
                    red_black_tree_left_rotate(tree, node);
                }
                node->parent->color = BLACK;
                node->parent->parent->color = RED;
                red_black_tree_right_rotate(tree, node->parent->parent);
            }
        } else {
            RedBlackTreeNode* uncle = node->parent->parent->left;
            if(uncle->color == RED) {
                node->parent->color = BLACK;
                uncle->color = BLACK;
                node->parent->parent->color = RED;
                node = node->parent->parent;
            } else {
                if(node == node->parent->left) {
                    node = node->parent;
                    red_black_tree_right_rotate(tree, node);
                }
                node->parent->color = BLACK;
                node->parent->parent->color = RED;
                red_black_tree_left_rotate(tree, node->parent->parent);
            }
        }
        if(node == tree->root) {
            break;
        }
    }
    tree->root->color = BLACK;
}
