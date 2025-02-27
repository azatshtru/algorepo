/// implementation adapted from
/// persistent_seg_tree_lazy_prop.cpp (https://github.com/TheAlgorithms/C-Plus-Plus/blob/master/range_queries/persistent_seg_tree_lazy_prop.cpp)
/// by Magdy Sedra (https://github.com/MSedra)

#include <stdio.h>
#include <stdlib.h>
#include "../headers/vector.h"

struct lazy_persistent_segtree_node {
    struct lazy_persistent_segtree_node* left;
    struct lazy_persistent_segtree_node* right;
    int value;
    int delta;
};

struct lazy_persistent_segtree {
    int n;
    vector(struct lazy_persistent_segtree_node*) roots;
    vector(int) data;
};

struct lazy_persistent_segtree_node* lazy_persistent_segtree_node_clone(struct lazy_persistent_segtree_node* node) {
    struct lazy_persistent_segtree_node* new_node = malloc(sizeof(struct lazy_persistent_segtree_node));
    new_node->left = node->left;
    new_node->right = node->right;
    new_node->delta = node->delta;
    new_node->value = node->value;
    return new_node;
}

void lazy_persistent_segtree_propagate(int i, int j, struct lazy_persistent_segtree_node* node) {
    if (!node->delta) {
        return;
    }
    node->value += (j - i + 1) * node->delta;
    if (i != j) {
        node->left = lazy_persistent_segtree_node_clone(node->left);
        node->right = lazy_persistent_segtree_node_clone(node->right);
        node->left->delta += node->delta;
        node->right->delta += node->delta;
    }
    node->delta = 0;
}

struct lazy_persistent_segtree_node* lazy_persistent_segtree_build(struct lazy_persistent_segtree* tree, int i, int j) {
    struct lazy_persistent_segtree_node* new_node = malloc(sizeof(struct lazy_persistent_segtree_node));
    if (i == j) {
        new_node->value = vec_get(tree->data, i);
    } else {
        int mid = i + (j - i) / 2;
        struct lazy_persistent_segtree_node* left = lazy_persistent_segtree_build(tree, i, mid);
        struct lazy_persistent_segtree_node* right = lazy_persistent_segtree_build(tree, mid + 1, j);
        new_node->value = left->value + right->value;
        new_node->left = left;
        new_node->right = right;
    }
    return new_node;
}

struct lazy_persistent_segtree_node* lazy_persistent_segtree_update(int i, int j, int l, int r, int value, struct lazy_persistent_segtree_node* node) {
    lazy_persistent_segtree_propagate(i, j, node);
    if (i >= l && j <= r) {
        struct lazy_persistent_segtree_node* new_node = lazy_persistent_segtree_node_clone(node);
        new_node->delta += value;
        lazy_persistent_segtree_propagate(i, j, new_node);
        return new_node;
    }
    if (i > r || j < l) {
        return node;
    }
    struct lazy_persistent_segtree_node* new_node = malloc(sizeof(struct lazy_persistent_segtree_node));
    int mid = i + (j - i) / 2;
    new_node->left = lazy_persistent_segtree_update(i, mid, l, r, value, node->left);
    new_node->right = lazy_persistent_segtree_update(mid + 1, j, l, r, value, node->right);
    new_node->value = new_node->left->value + new_node->right->value;
    return new_node;
}

int lazy_persistent_segtree_query(int i, int j, int l, int r, struct lazy_persistent_segtree_node* node) {
    lazy_persistent_segtree_propagate(i, j, node);
    if (j < l || r < i) {
        return 0;
    }
    if (i >= l && j <= r) {
        return node->value;
    }
    int mid = i + (j - i) / 2;
    return lazy_persistent_segtree_query(i, mid, l, r, node->left)
           + lazy_persistent_segtree_query(mid + 1, j, l, r, node->right);
}

void lazy_persistent_segtree_new(struct lazy_persistent_segtree* tree, vector(int) data) {
    if (vec_len(data) == 0) return;
    tree->n = vec_len(data);
    tree->data = data;
    tree->roots = vec_new(struct lazy_persistent_segtree_node*);
    struct lazy_persistent_segtree_node* root = lazy_persistent_segtree_build(tree, 0, tree->n - 1);
    vec_push(tree->roots, root);
}

void lazy_persistent_segtree_update_push(struct lazy_persistent_segtree* tree, int l, int r, int value) {
    vec_push(tree->roots, lazy_persistent_segtree_update(
        0, tree->n - 1, l, r, value,
        vec_get(tree->roots, vec_len(tree->roots) - 1)
    ));
}

int lazy_persistent_segtree_query_version(struct lazy_persistent_segtree* tree, int l, int r, int version) {
    return lazy_persistent_segtree_query(0, tree->n - 1, l, r, vec_get(tree->roots, version));
}

int lazy_persistent_segtree_versions(struct lazy_persistent_segtree* tree) {
    return vec_len(tree->roots);
}

int main() {
    vector(int) arr = vec_new(int);
    int things[8] = { -5, 2, 3, 11, -2, 7, 0, 1 };
    for(int i = 0; i < 8; i++) {
        vec_push(arr, things[i]);
    }
    struct lazy_persistent_segtree tree;
    printf("base array before any updates { ");
    for(int i = 0; i < vec_len(arr); i++) {
        printf("%d, ", vec_get(arr, i));
    }
    printf("\b\b }\n\n");
    lazy_persistent_segtree_new(&tree, arr);

    printf(
        "QUERY range sum on version 0 from index 2 to 4 (3 + 11 - 2) -> %d\n\n",
        lazy_persistent_segtree_query_version(&tree, 2, 4, 0)
    );

    printf("UPDATE subtract 7 to elements from index 1 to 5 inclusive\n");
    lazy_persistent_segtree_update_push(&tree, 1, 5, -7);
    printf("base array of segtree version 1 { ");
    for (int i = 0; i < vec_len(arr); ++i) {
        printf("%d, ", lazy_persistent_segtree_query_version(&tree, i, i, 1));
    }
    printf("\b\b }\n\n");

    printf("UPDATE add 10 to elements from index 0 to 7 inclusive\n");
    lazy_persistent_segtree_update_push(&tree, 0, 7, 10);
    printf("base array of segtree version { ");
    for (int i = 0; i < vec_len(arr); ++i) {
        printf("%d, ", lazy_persistent_segtree_query_version(&tree, i, i, 2));
    }
    printf("\b\b }\n\n");

    printf("number of segment tree versions -> %d\n", lazy_persistent_segtree_versions(&tree));
    printf("QUERY range sum on version 0 from index 3 to 5 (11 - 2 + 7) -> %d\n", lazy_persistent_segtree_query_version(&tree, 3, 5, 0));
    printf("QUERY range sum on version 1 from index 3 to 5 (4 - 9 + 0) -> %d\n", lazy_persistent_segtree_query_version(&tree, 3, 5, 1));

    return 0;
}
