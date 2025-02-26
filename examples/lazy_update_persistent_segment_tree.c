/// adapted from Magdy Sedra's persistent segment tree with lazy propagation
/// https://github.com/MSedra

#include <stdio.h>
#include <stdlib.h>
#include "../headers/vector.h"

struct Node {
    struct Node* left;
    struct Node* right;
    int val;
    int prop;
};

struct perSegTree {
    int n;
    vector(struct Node*) ptrs;
    vector(int) vec;
};

struct Node* newKid(struct Node* curr) {
    struct Node* newNode = malloc(sizeof(struct Node));
    newNode->left = curr->left;
    newNode->right = curr->right;
    newNode->prop = curr->prop;
    newNode->val = curr->val;
    return newNode;
}

void lazy(int i, int j, struct Node* curr) {
    if (!curr->prop) {
        return;
    }
    curr->val += (j - i + 1) * curr->prop;
    if (i != j) {
        curr->left = newKid(curr->left);
        curr->right = newKid(curr->right);
        curr->left->prop += curr->prop;
        curr->right->prop += curr->prop;
    }
    curr->prop = 0;
}

struct Node* construct(struct perSegTree* tree, int i, int j) {
    struct Node* newNode = malloc(sizeof(struct Node));
    if (i == j) {
        newNode->val = vec_get(tree->vec, i);
    } else {
        int mid = i + (j - i) / 2;
        struct Node* leftt = construct(tree, i, mid);
        struct Node* right = construct(tree, mid + 1, j);
        newNode->val = leftt->val + right->val;
        newNode->left = leftt;
        newNode->right = right;
    }
    return newNode;
}

struct Node* update(int i, int j, int l, int r, int value, struct Node* curr) {
    lazy(i, j, curr);
    if (i >= l && j <= r) {
        struct Node* newNode = newKid(curr);
        newNode->prop += value;
        lazy(i, j, newNode);
        return newNode;
    }
    if (i > r || j < l) {
        return curr;
    }
    struct Node* newNode = malloc(sizeof(struct Node));
    int mid = i + (j - i) / 2;
    newNode->left = update(i, mid, l, r, value, curr->left);
    newNode->right = update(mid + 1, j, l, r, value, curr->right);
    newNode->val = newNode->left->val + newNode->right->val;
    return newNode;
}

int query(int i, int j, int l, int r, struct Node* curr) {
    lazy(i, j, curr);
    if (j < l || r < i) {
        return 0;
    }
    if (i >= l && j <= r) {
        return curr->val;
    }
    int mid = i + (j - i) / 2;
    return query(i, mid, l, r, curr->left)
           + query(mid + 1, j, l, r, curr->right);
}

void pub_construct(struct perSegTree* tree, vector(int) vec) {
    if (vec_len(vec) == 0) return;
    tree->n = vec_len(vec);
    tree->vec = vec;
    tree->ptrs = vec_new(struct Node*);
    struct Node* root = construct(tree, 0, tree->n - 1);
    vec_push(tree->ptrs, root);
}

void pub_update(struct perSegTree* tree, int l, int r, int value) {
    vec_push(tree->ptrs, update(
        0, tree->n - 1, l, r, value,
        vec_get(tree->ptrs, vec_len(tree->ptrs) - 1)
    ));
}

int pub_query(struct perSegTree* tree, int l, int r, int version) {
    return query(0, tree->n - 1, l, r, vec_get(tree->ptrs, version));
}

int size(struct perSegTree* tree) {
    return vec_len(tree->ptrs);
}

#include "../tests/orange_juice.h"
#include "../headers/logging.h"

oj_test(lazy_update_persistent_segment_tree_query_tests) {
    vector(int) arr = vec_new(int);
    int things[8] = { -5, 2, 3, 11, -2, 7, 0, 1 };
    for(int i = 0; i < 8; i++) {
        vec_push(arr, things[i]);
    }
    struct perSegTree tree;
    log_label("elements before any updates");
    log_array(vec_as_array(arr), int, vec_len(arr), x, printf("%d", x));
    pub_construct(&tree, arr);

    log_int(
        "Querying range sum on version 0 from index 2 to 4 = 3+11-2 = ",
        pub_query(&tree, 2, 4, 0)
    );

    log_label("Subtract 7 from all elements from index 1 to index 5 inclusive");
    pub_update(&tree, 1, 5, -7);
    log_label("elements of segment tree whose version = 1 (after 1 update)");
    log_array(vec_as_array(arr), int, vec_len(arr), x, printf("%d", x));

    log_label("Add 10 to all elements from index 0 to index 7 inclusive");
    pub_update(&tree, 0, 7, 10);
    log_label("elements of the segment tree whose version = 2 (after 2 updates)");
    log_array(vec_as_array(arr), int, vec_len(arr), x, printf("%d", x));

    log_int("Number of segment trees (versions) now ", size(&tree));
    log_int("Querying range sum on version 0 from index 3 to 5 = 11-2+7 = ", pub_query(&tree, 3, 5, 0));
    log_int("Querying range sum on version 1 from index 3 to 5 = 4-9+0 = ", pub_query(&tree, 3, 5, 1));

    oj_rotten;
}

oj_prepare(lazy_update_persistent_segment_tree_tests) {
    oj_run(lazy_update_persistent_segment_tree_query_tests);
    oj_report;
    oj_fresh;
}

int main() {
    oj_blend(lazy_update_persistent_segment_tree_tests, 0);
    return 0;
}
