#include <stdlib.h>
#include "vector.h"

#ifndef BTREE
#define BTREE

struct btree_node {
    vector(int) keys;
    vector(struct btree_node) children;
    int is_leaf;
};

struct btree {
    struct btree_node* root;
    int degree;
};

int btree_init(struct btree* btree, int degree);
int btree_node_init(struct btree_node* node_ptr, int is_leaf);
struct btree_node* btree_search(struct btree btree, int key, struct btree_node* node);
void btree_split_child(struct btree* btree, struct btree_node* x, int i);

#endif
