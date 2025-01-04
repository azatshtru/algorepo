#include <stdio.h>
#include <stdlib.h>
#include "../headers/miniqutils.h"

#ifndef RED_BLACK_TREES
#define RED_BLACK_TREES

#define RED 1
#define BLACK 0
#define Color int

struct red_black_tree_node {
    int key;
    struct red_black_tree_node* parent;
    Color color;

    struct red_black_tree_node* left;
    struct red_black_tree_node* right;
};

struct red_black_tree {
    struct red_black_tree_node* nil;
    struct red_black_tree_node* root;
};

typedef struct red_black_tree_node RedBlackTreeNode;
typedef struct red_black_tree RedBlackTree;

RedBlackTreeNode* red_black_tree_node_new(int key);
RedBlackTree red_black_tree_new();

void red_black_tree_left_rotate(RedBlackTree* tree, RedBlackTreeNode* node);
void red_black_tree_right_rotate(RedBlackTree* tree, RedBlackTreeNode* node);
void red_black_tree_insert(RedBlackTree* tree, int key);
void red_black_tree_insert_fixup(RedBlackTree* tree, RedBlackTreeNode* node);

RedBlackTreeNode* red_black_tree_minimum(RedBlackTree* tree, RedBlackTreeNode* node);
RedBlackTreeNode* red_black_tree_search(RedBlackTree* tree, int key);

int red_black_tree_delete(RedBlackTree* tree, int key);
void red_black_tree_transplant(RedBlackTree* tree, RedBlackTreeNode* host, RedBlackTreeNode* graft);
void red_black_tree_delete_fixup(RedBlackTree* tree, RedBlackTreeNode* sibling);

#endif
