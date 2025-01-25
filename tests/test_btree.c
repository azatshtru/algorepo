#include "../headers/btree.h"
#include "orange_juice.h"

oj_test(btree_initializes) {
    BTree tree = btree_new(3);
    oj_assert_eq_int(3, tree.degree);
    oj_assert_eq_int(1, tree.root->is_leaf);
    oj_fresh;
}

oj_test(btree_node_initializes) {
    struct btree_node* node = btree_node_new(0);
    oj_assert_eq_int(0, node->is_leaf);
    oj_assert(node->children != NULL, "");
    oj_assert(node->keys != NULL, "");
    oj_fresh;
}

oj_test(btree_insert_5_keys_into_root) {
    BTree tree = btree_new(3);
    btree_insert(&tree, 9);
    btree_insert(&tree, 7);
    btree_insert(&tree, 41);
    btree_insert(&tree, 20);
    btree_insert(&tree, 48);

    oj_assert_eq_int(7, vec_get(tree.root->keys, 0));
    oj_assert_eq_int(9, vec_get(tree.root->keys, 1));
    oj_assert_eq_int(20, vec_get(tree.root->keys, 2));
    oj_assert_eq_int(41, vec_get(tree.root->keys, 3));
    oj_assert_eq_int(48, vec_get(tree.root->keys, 4));
    oj_fresh;
}

oj_test(btree_node_split_keys_splits_the_node_keys_and_returns_the_split_key) {
    BTree tree = btree_new(3);
    btree_insert(&tree, 9);
    btree_insert(&tree, 7);
    btree_insert(&tree, 41);
    btree_insert(&tree, 20);
    btree_insert(&tree, 48);

    struct btree_node* split_node = btree_node_new(1);
    int split_key = btree_node_split_keys(tree.root, split_node, tree.degree);

    oj_assert_eq_int(20, split_key);

    oj_assert_eq_int(2, vec_len(tree.root->keys));
    oj_assert_eq_int(2, vec_len(split_node->keys));

    oj_assert_eq_int(7, vec_get(tree.root->keys, 0));
    oj_assert_eq_int(9, vec_get(tree.root->keys, 1));
    oj_assert_eq_int(41, vec_get(split_node->keys, 0));
    oj_assert_eq_int(48, vec_get(split_node->keys, 1));

    oj_fresh;
}

oj_test(btree_node_index_by_key_returns_the_index_of_key) {
    BTree tree = btree_new(3);
    btree_insert(&tree, 9);
    btree_insert(&tree, 7);
    btree_insert(&tree, 41);
    btree_insert(&tree, 20);
    btree_insert(&tree, 48);

    oj_assert_eq_int(3, btree_node_index_by_key(tree.root, 41));
    oj_assert_eq_int(3, btree_node_index_by_key(tree.root, 27));
    oj_assert_eq_int(1, btree_node_index_by_key(tree.root, 9));
    oj_assert_eq_int(2, btree_node_index_by_key(tree.root, 15));

    oj_fresh;
}

oj_test(btree_node_key_by_index_returns_the_key_at_index) {
    BTree tree = btree_new(3);
    btree_insert(&tree, 9);
    btree_insert(&tree, 7);
    btree_insert(&tree, 41);
    btree_insert(&tree, 20);
    btree_insert(&tree, 48);

    oj_assert_eq_int(7, btree_node_key_by_index(tree.root, 0));
    oj_assert_eq_int(9, btree_node_key_by_index(tree.root, 1));
    oj_assert_eq_int(20, btree_node_key_by_index(tree.root, 2));
    oj_assert_eq_int(41, btree_node_key_by_index(tree.root, 3));
    oj_assert_eq_int(48, btree_node_key_by_index(tree.root, 4));

    oj_fresh;
    oj_fresh;
}

oj_test(btree_node_key_mutation_tests) {
    struct btree_node* node = btree_node_new(1);
    btree_node_insert_key(node, 9);
    btree_node_insert_key(node, 4);
    btree_node_insert_key(node, 2);
    btree_node_insert_key(node, 6);
    btree_node_insert_key(node, 3);

    oj_assert_eq_int(2, btree_node_key_by_index(node, 0));
    oj_assert_eq_int(3, btree_node_key_by_index(node, 1));
    oj_assert_eq_int(4, btree_node_key_by_index(node, 2));
    oj_assert_eq_int(6, btree_node_key_by_index(node, 3));
    oj_assert_eq_int(9, btree_node_key_by_index(node, 4));

    int r1 = btree_node_remove_key(node, 9);
    int r2 = btree_node_remove_key(node, 5);

    oj_assert_eq_int(4, vec_len(node->keys));
    
    oj_assert_eq_int(9, r1);
    oj_assert_eq_int(-1, r2);

    oj_fresh;
}

oj_test(btree_split_children_splits_children_between_node_and_split_node) {
    struct btree_node* node = btree_node_new(0);
    btree_node_insert_key(node, 9);
    btree_node_insert_key(node, 4);
    btree_node_insert_key(node, 2);
    btree_node_insert_key(node, 6);
    btree_node_insert_key(node, 3);

    struct btree_node* n1 = btree_node_new(1);
    struct btree_node* n2 = btree_node_new(1);
    struct btree_node* n3 = btree_node_new(1);
    struct btree_node* n4 = btree_node_new(1);
    struct btree_node* n5 = btree_node_new(1);
    struct btree_node* n6 = btree_node_new(1);

    btree_node_push_child(node, n1);
    btree_node_push_child(node, n2);
    btree_node_push_child(node, n3);
    btree_node_push_child(node, n4);
    btree_node_push_child(node, n5);
    btree_node_push_child(node, n6);
    oj_assert_eq_int(6, vec_len(node->children));

    struct btree_node* split_node = btree_node_new(0);
    btree_node_split_keys(node, split_node, 3);
    btree_node_split_children(node, split_node, 3);

    oj_assert_eq_int(3, vec_len(split_node->children));
    oj_assert_eq_pointer(n4, btree_node_child_at_index(split_node, 0));
    oj_assert_eq_pointer(n5, btree_node_child_at_index(split_node, 1));
    oj_assert_eq_pointer(n6, btree_node_child_at_index(split_node, 2));

    oj_assert_eq_int(3, vec_len(node->children));
    oj_assert_eq_pointer(n1, btree_node_child_at_index(node, 0));
    oj_assert_eq_pointer(n2, btree_node_child_at_index(node, 1));
    oj_assert_eq_pointer(n3, btree_node_child_at_index(node, 2));

    oj_fresh;
}

oj_test(test_btree_node_push_child) {
    struct btree_node* node = btree_node_new(0);
    btree_node_insert_key(node, 42);
    btree_node_insert_key(node, 27);
    btree_node_insert_key(node, 75);
    struct btree_node* n1 = btree_node_new(1);
    struct btree_node* n2 = btree_node_new(1);
    struct btree_node* n3 = btree_node_new(1);
    struct btree_node* n4 = btree_node_new(1);

    btree_node_push_child(node, n1);
    btree_node_push_child(node, n2);

    oj_assert_eq_pointer(n1, vec_get(node->children, 0));
    oj_assert_eq_pointer(n2, vec_get(node->children, 1));

    btree_node_push_child(node, n3);
    oj_assert_eq_int(3, vec_len(node->children));
    oj_assert_eq_pointer(n3, vec_get(node->children, 2));

    btree_node_push_child(node, n4);
    oj_assert_eq_int(4, vec_len(node->children));
    oj_assert_eq_pointer(n4, vec_get(node->children, 3));
    
    oj_fresh;
}

oj_test(btree_node_first_child_returns_first_child_of_node) {
    struct btree_node* node = btree_node_new(0);
    btree_node_insert_key(node, 42);
    btree_node_insert_key(node, 27);
    btree_node_insert_key(node, 75);
    struct btree_node* n1 = btree_node_new(1);
    struct btree_node* n2 = btree_node_new(1);
    struct btree_node* n3 = btree_node_new(1);
    struct btree_node* n4 = btree_node_new(1);
    btree_node_push_child(node, n1);
    btree_node_push_child(node, n2);
    btree_node_push_child(node, n3);

    oj_assert_eq_pointer(n1, btree_node_first_child(node));
    oj_fresh;
}

oj_test(btree_node_child_after_key_returns_child_after_given_key) {
    struct btree_node* node = btree_node_new(0);
    btree_node_insert_key(node, 42);
    btree_node_insert_key(node, 27);
    btree_node_insert_key(node, 75);
    struct btree_node* n1 = btree_node_new(1);
    struct btree_node* n2 = btree_node_new(1);
    struct btree_node* n3 = btree_node_new(1);
    struct btree_node* n4 = btree_node_new(1);
    btree_node_push_child(node, n1);
    btree_node_push_child(node, n2);
    btree_node_push_child(node, n3);
    btree_node_push_child(node, n4);

    oj_assert_eq_pointer(n4, btree_node_child_after_key(node, 75));
    oj_assert_eq_pointer(n3, btree_node_child_after_key(node, 42));
    oj_assert_eq_pointer(n2, btree_node_child_after_key(node, 27));
    oj_fresh;
}

oj_test(test_btree_node_empty_queries) {
    struct btree_node* node = btree_node_new(1);
    oj_assert_eq_int(1, btree_node_is_empty(node));
    btree_node_insert_key(node, 42);
    oj_assert_eq_int(0, btree_node_is_empty(node));
    oj_fresh;
}

oj_test(btree_node_contains_key_returns_true_if_key_is_in_node) {
    struct btree_node* node = btree_node_new(0);
    btree_node_insert_key(node, 42);
    btree_node_insert_key(node, 11);
    btree_node_insert_key(node, 37);

    oj_assert_eq_int(1, btree_node_contains_key(node, 42));
    oj_assert_eq_int(1, btree_node_contains_key(node, 11));
    oj_assert_eq_int(0, btree_node_contains_key(node, 13));

    oj_fresh;
}

oj_test(btree_split_full_node_splits_keys_and_children_of_node_into_split_node) {
    BTree btree = btree_new(3);
    btree_insert(&btree, 9);
    btree_insert(&btree, 4);
    btree_insert(&btree, 2);
    btree_insert(&btree, 6);
    btree_insert(&btree, 3);
    btree.root->is_leaf = 0;

    struct btree_node* n1 = btree_node_new(1);
    struct btree_node* n2 = btree_node_new(1);
    struct btree_node* n3 = btree_node_new(1);
    struct btree_node* n4 = btree_node_new(1);
    struct btree_node* n5 = btree_node_new(1);
    struct btree_node* n6 = btree_node_new(1);

    btree_node_push_child(btree.root, n1);
    btree_node_push_child(btree.root, n2);
    btree_node_push_child(btree.root, n3);
    btree_node_push_child(btree.root, n4);
    btree_node_push_child(btree.root, n5);
    btree_node_push_child(btree.root, n6);
    oj_assert_eq_int(6, vec_len(btree.root->children));

    struct btree_node* split_node = btree_node_new(0);

    btree_split_full_node(&btree, btree.root, split_node);

    oj_assert_eq_int(3, vec_len(split_node->children));
    oj_assert_eq_pointer(n4, btree_node_child_at_index(split_node, 0));
    oj_assert_eq_pointer(n5, btree_node_child_at_index(split_node, 1));
    oj_assert_eq_pointer(n6, btree_node_child_at_index(split_node, 2));

    oj_assert_eq_int(3, vec_len(btree.root->children));
    oj_assert_eq_pointer(n1, btree_node_child_at_index(btree.root, 0));
    oj_assert_eq_pointer(n2, btree_node_child_at_index(btree.root, 1));
    oj_assert_eq_pointer(n3, btree_node_child_at_index(btree.root, 2));

    oj_fresh;
}

oj_test(btree_node_insert_child_inserts_child_at_index) {
    struct btree_node* node = btree_node_new(0);
    struct btree_node* n1 = btree_node_new(1);
    struct btree_node* n2 = btree_node_new(1);
    struct btree_node* n3 = btree_node_new(1);
    struct btree_node* n4 = btree_node_new(1);
    btree_node_push_child(node, n1);
    btree_node_push_child(node, n2);
    btree_node_push_child(node, n3);

    btree_node_insert_child(node, 1, n4);

    oj_assert_eq_pointer(n4, btree_node_child_at_index(node, 1));
    oj_assert_eq_pointer(n2, btree_node_child_at_index(node, 2));
    oj_assert_eq_pointer(n3, btree_node_child_at_index(node, 3));
    oj_assert_eq_pointer(n1, btree_node_child_at_index(node, 0));

    oj_fresh;
}

oj_test(btree_split_child_splits_the_ith_child_and_returns_the_split_node) {
    BTree btree = btree_new(3);
    btree_insert(&btree, 9);
    btree.root->is_leaf = 0;

    struct btree_node* node = btree_node_new(0);
    btree_node_insert_key(node, 12);
    btree_node_insert_key(node, 67);
    btree_node_insert_key(node, 42);
    btree_node_insert_key(node, 31);
    btree_node_insert_key(node, 6);

    struct btree_node* n1 = btree_node_new(1);
    struct btree_node* n2 = btree_node_new(1);
    struct btree_node* n3 = btree_node_new(1);
    struct btree_node* n4 = btree_node_new(1);
    struct btree_node* n5 = btree_node_new(1);
    struct btree_node* n6 = btree_node_new(1);

    struct btree_node* node_dash = btree_node_new(0);
    btree_node_push_child(btree.root, node);
    btree_node_push_child(btree.root, node_dash);

    btree_node_push_child(node, n1);
    btree_node_push_child(node, n2);
    btree_node_push_child(node, n3);
    btree_node_push_child(node, n4);
    btree_node_push_child(node, n5);
    btree_node_push_child(node, n6);

    struct btree_node* split_node = btree_split_child(&btree, btree.root, 0);

    oj_assert_eq_int(3, vec_len(node->children));
    oj_assert_eq_pointer(n1, btree_node_child_at_index(node, 0));
    oj_assert_eq_pointer(n2, btree_node_child_at_index(node, 1));
    oj_assert_eq_pointer(n3, btree_node_child_at_index(node, 2));

    oj_assert_eq_int(3, vec_len(split_node->children));
    oj_assert_eq_pointer(n4, btree_node_child_at_index(split_node, 0));
    oj_assert_eq_pointer(n5, btree_node_child_at_index(split_node, 1));
    oj_assert_eq_pointer(n6, btree_node_child_at_index(split_node, 2));

    oj_fresh;
}

oj_prepare(btree_insertion_tests) {
    oj_run(btree_insert_5_keys_into_root);
    oj_report;
    oj_fresh;
}

oj_prepare(btree_split_tests) {
    oj_run(btree_node_split_keys_splits_the_node_keys_and_returns_the_split_key);
    oj_run(btree_split_children_splits_children_between_node_and_split_node);
    oj_run(btree_split_full_node_splits_keys_and_children_of_node_into_split_node);
    oj_run(btree_split_child_splits_the_ith_child_and_returns_the_split_node);
    oj_report;
    oj_fresh;
}

oj_prepare(btree_node_queries_tests) {
    oj_run(btree_node_index_by_key_returns_the_index_of_key);
    oj_run(btree_node_key_by_index_returns_the_key_at_index);
    oj_run(btree_node_first_child_returns_first_child_of_node);
    oj_run(btree_node_child_after_key_returns_child_after_given_key);
    oj_run(btree_node_contains_key_returns_true_if_key_is_in_node);
    oj_run(test_btree_node_empty_queries);
    oj_report;
    oj_fresh;
}

oj_prepare(btree_node_mutation_tests) {
    oj_run(btree_node_key_mutation_tests);
    oj_run(test_btree_node_push_child);
    oj_run(btree_node_insert_child_inserts_child_at_index);
    oj_report;
    oj_fresh;
}

oj_prepare(btree_setup_tests) {
    oj_run(btree_initializes);
    oj_run(btree_node_initializes);
    oj_report;
    oj_fresh;
}

int main() {
    oj_blend(btree_node_queries_tests, 0);
    oj_blend(btree_node_mutation_tests, 0);
    oj_blend(btree_setup_tests, 0);
    oj_blend(btree_insertion_tests, 0);
    oj_blend(btree_split_tests, 0);
    return 0;
}
