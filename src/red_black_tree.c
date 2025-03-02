#include "../headers/red_black_tree.h"

RedBlackTreeNode* red_black_tree_node_new(int key) {
    struct red_black_tree_node* node = malloc(sizeof(struct red_black_tree_node));
    node->parent = NULL;
    node->color = RED;
    node->left = NULL;
    node->right = NULL;
    node->key = key;
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

RedBlackTreeNode* red_black_tree_minimum(RedBlackTree* tree, RedBlackTreeNode* node) {
    while(node->left != tree->nil) {
        node = node->left;
    }
    return node;
}

RedBlackTreeNode* red_black_tree_search(RedBlackTree* tree, int key) {
    RedBlackTreeNode* node = tree->root;
    while(node != tree->nil && key != node->key) {
        if(key < node->key) {
            node = node->left;
        } else {
            node = node->right;
        }
    }
    return node;
}

int red_black_tree_delete(RedBlackTree* tree, int key) {
    RedBlackTreeNode* deleted = red_black_tree_search(tree, key);

    if(deleted == tree->nil) {
        return -1;
    }

    RedBlackTreeNode* successor = deleted; // the in-order successor
    Color deleted_original_color = successor->color;

    RedBlackTreeNode* node; 

    if(deleted->left == tree->nil) {
        node = deleted->right;
        red_black_tree_transplant(tree, deleted, deleted->right);
    } else if(deleted->right == tree->nil) {
        node = deleted->left;
        red_black_tree_transplant(tree, deleted, deleted->left);
    } else {
        successor = red_black_tree_minimum(tree, deleted->right);
        deleted_original_color = successor->color;
        node = successor->right;
        
        if(successor->parent == deleted) {
            node->parent = successor;
        } else {
            red_black_tree_transplant(tree, successor, successor->right);
            successor->right = deleted->right;
            successor->right->parent = successor;
        }
        red_black_tree_transplant(tree, deleted, successor);
        successor->left = deleted->left;
        successor->left->parent = successor; 
        successor->color = deleted->color;
    }
    
    if(deleted_original_color == BLACK) {
        red_black_tree_delete_fixup(tree, node);
    }
    return 0;
}

void red_black_tree_delete_fixup(RedBlackTree* tree, RedBlackTreeNode* node) {
    while(node != tree->root && node->color == BLACK) {
        if(node == node->parent->left) {
            RedBlackTreeNode* sibling = node->parent->right;
            // sibling is red
            if(sibling->color == RED) {
                sibling->color = BLACK;
                node->parent->color = RED;
                red_black_tree_left_rotate(tree, node->parent);
                sibling = node->parent->right;
            }
            // sibling and both its children are black
            if(sibling->left->color == BLACK && sibling->right->color == BLACK) {
                sibling->color = RED;
                node = node->parent; 
            } else {
                // sibling and its same side child is black, and its opposite side child is red
                if(sibling->right->color == BLACK) {
                    sibling->left->color = BLACK;
                    sibling->color = RED;
                    red_black_tree_right_rotate(tree, sibling);
                    sibling = node->parent->right;
                }
                // sibling is black and its same side child is red
                sibling->color = node->parent->color;
                node->parent->color = BLACK;
                sibling->right->color = BLACK;
                red_black_tree_left_rotate(tree, node->parent);
                node = tree->root;
            }
        } else {
            RedBlackTreeNode* sibling = node->parent->left;
            if(sibling->color == RED) {
                sibling->color = BLACK;
                node->parent->color = RED;
                red_black_tree_right_rotate(tree, node->parent);
                sibling = node->parent->left;
            }
            if(sibling->right->color == BLACK && sibling->left->color == BLACK) {
                sibling->color = RED;
                node = node->parent; 
            } else {
                if(sibling->left->color == BLACK) {
                    sibling->right->color = BLACK;
                    sibling->color = RED;
                    red_black_tree_left_rotate(tree, sibling);
                    sibling = node->parent->left;
                }
                sibling->color = node->parent->color;
                node->parent->color = BLACK;
                sibling->left->color = BLACK;
                red_black_tree_right_rotate(tree, node->parent);
                node = tree->root;
            }
        }
    }
    node->color = BLACK;
}

void red_black_tree_transplant(RedBlackTree* tree, RedBlackTreeNode* host, RedBlackTreeNode* graft) {
    if(host->parent == NULL) {
        tree->root = graft;
    } else if(host == host->parent->left) {
        host->parent->left = graft;
    } else {
        host->parent->right = graft;
    }
    graft->parent = host->parent;
}

void red_black_tree_levelwise_traverse_and_print_keys(RedBlackTree* tree) {
    VecDeque(struct red_black_tree_node*) q = queue_new(struct red_black_tree_node*);
    queue_push_back(q, tree->root);

    while(!queue_is_empty(q)) {
        struct red_black_tree_node* node = queue_pop_front(q);
        printf("%d ", node->key);
        if(node->left != tree->nil) {
            queue_push_back(q, node->left);
        }
        if(node->right != tree->nil) {
            queue_push_back(q, node->right);
        }
    }
    printf("\n");
    queue_free(q, NULL);
}

void red_black_tree_free(RedBlackTree* tree) {
    VecDeque(struct red_black_tree_node*) q = queue_new(struct red_black_tree_node*);
    queue_push_back(q, tree->root);

    while(!queue_is_empty(q)) {
        struct red_black_tree_node* node = queue_pop_front(q);
        if(node->left != tree->nil) {
            queue_push_back(q, node->left);
        }
        if(node->right != tree->nil) {
            queue_push_back(q, node->right);
        }
        free(node);
    }
    queue_free(q, NULL);
    free(tree->nil);
}
