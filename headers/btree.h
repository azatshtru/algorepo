#include <stdlib.h>
#include "vector.h"
#include "queue.h"

#ifndef BTREE
#define BTREE

struct btree_node {
    vector(int) keys;
    vector(struct btree_node*) children;
    int is_leaf;
};

typedef struct btree {
    struct btree_node* root;
    int degree;
} BTree;

struct btree_node* btree_node_new(int is_leaf);
int btree_node_init(struct btree_node* node_ptr, int is_leaf);

int btree_node_is_empty(struct btree_node* node);
int btree_node_is_full(struct btree_node* node, int degree);

void btree_node_split_children(struct btree_node* node, struct btree_node* split_node, int degree);
int btree_node_split_keys(struct btree_node* node, struct btree_node* split_node, int degree);

int btree_node_key_by_index(struct btree_node* node, int index);
int btree_node_index_by_key(struct btree_node* node, int key);
int btree_node_contains_key(struct btree_node* node, int key);

struct btree_node* btree_node_first_child(struct btree_node* node);
struct btree_node* btree_node_child_after_key(struct btree_node* node, int key);
struct btree_node* btree_node_child_at_index(struct btree_node* node, int index);

void btree_node_insert_key(struct btree_node* node, int key);
int btree_node_remove_key(struct btree_node* node, int key);

void btree_node_push_child(struct btree_node* node, struct btree_node* child_node);
void btree_node_insert_child(struct btree_node* node, int index, struct btree_node* child_node);
void btree_node_remove_child(struct btree_node* node, struct btree_node* child_node);


BTree btree_new(int degree);
int btree_init(struct btree* btree, int degree);

int btree_split_full_node(struct btree* btree, struct btree_node* node, struct btree_node* split_node);
struct btree_node* btree_split_child(struct btree* btree, struct btree_node* x, int i);

struct btree_node* btree_search(struct btree* btree, int key, struct btree_node* node);

void btree_insert_into_non_full(struct btree* btree, struct btree_node* x, int key);
void btree_insert(struct btree* btree, int key);

void btree_delete(struct btree* btree, struct btree_node* node, int key);
void btree_delete_internal_node(BTree* btree, struct btree_node* node, int key, int i);
int btree_delete_predecessor(BTree* btree, struct btree_node* node);
int btree_delete_successor(BTree* btree, struct btree_node* node);
void btree_delete_merge(BTree* btree, struct btree_node* node, int i, int j);
void btree_delete_sibling(BTree* btree, struct btree_node* node, int i, int j);

void btree_levelwise_traverse_and_print_keys(BTree* btree);

#endif
