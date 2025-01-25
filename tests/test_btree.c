#include <stdarg.h>
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

int test_btree_node_values(struct btree_node* node, int n, ...) {
    va_list args;
    va_start(args, n);

    for(int i = 0; i < n; i++) {
        int expected = btree_node_key_by_index(node, i);
        int result = va_arg(args, int);
        if(result != expected) {
            return 0;
        }
    }

    va_end(args);
    return 1;
}

oj_test(test_btree_insert_100_keys_increasing_order) {
    BTree btree = btree_new(3); 
    for(int i = 0; i < 100; i++) {
        btree_insert(&btree, i);
    }

    oj_assert_eq_int(1, test_btree_node_values(btree.root, 2, 26, 53));
    struct btree_node* l1n0 = btree_node_child_at_index(btree.root, 0);
    struct btree_node* l1n1 = btree_node_child_at_index(btree.root, 1);
    struct btree_node* l1n2 = btree_node_child_at_index(btree.root, 2);

    oj_assert_eq_int(1, test_btree_node_values(l1n0, 2, 8, 17));
    oj_assert_eq_int(1, test_btree_node_values(l1n1, 2, 35, 44));
    oj_assert_eq_int(1, test_btree_node_values(l1n2, 4, 62, 71, 80, 89));

    struct btree_node* l2n10 = btree_node_child_at_index(l1n2, 4);
    oj_assert_eq_int(1, test_btree_node_values(l2n10, 2, 92, 95));
    oj_assert_eq_int(1, test_btree_node_values(btree_node_child_at_index(l2n10, 2), 4, 96, 97, 98, 99));

    // Level 0: 26 53
    //
    // Level 1: 8 17
    // Level 1: 35 44
    // Level 1: 62 71 80 89
    //
    // Level 2: 2 5
    // Level 2: 11 14
    // Level 2: 20 23
    //
    // Level 2: 29 32
    // Level 2: 38 41
    // Level 2: 47 50
    //
    // Level 2: 56 59
    // Level 2: 65 68
    // Level 2: 74 77
    // Level 2: 83 86
    // Level 2: 92 95
    //
    // Level 3: 0 1
    // Level 3: 3 4
    // Level 3: 6 7
    //
    // Level 3: 9 10
    // Level 3: 12 13
    // Level 3: 15 16
    //
    // Level 3: 18 19
    // Level 3: 21 22
    // Level 3: 24 25
    //
    // Level 3: 27 28
    // Level 3: 30 31
    // Level 3: 33 34
    //
    // Level 3: 36 37
    // Level 3: 39 40
    // Level 3: 42 43
    //
    // Level 3: 45 46
    // Level 3: 48 49
    // Level 3: 51 52
    //
    // Level 3: 54 55
    // Level 3: 57 58
    // Level 3: 60 61
    //
    // Level 3: 63 64
    // Level 3: 66 67
    // Level 3: 69 70
    //
    // Level 3: 72 73
    // Level 3: 75 76
    // Level 3: 78 79
    //
    // Level 3: 81 82
    // Level 3: 84 85
    // Level 3: 87 88
    //
    // Level 3: 90 91
    // Level 3: 93 94
    // Level 3: 96 97 98 99

    oj_fresh;
}

oj_test(test_btree_insert_100_random_keys) {
    BTree btree = btree_new(3); 
    int keys[100] = {
        808, 623, 687, 746, 715, 948, 200, 110, 322, 7, 488,
        698, 852, 798, 156, 267, 908, 964, 429, 358, 70, 788, 900, 802, 881,
        191, 216, 968, 603, 25, 157, 309, 311, 739, 180, 843, 401, 498, 622,
        81, 816, 529, 187, 253, 59, 287, 351, 824, 600, 847, 322, 390, 504,
        661, 470, 222, 963, 834, 963, 203, 974, 695, 561, 333, 577, 382, 778,
        136, 671, 562, 765, 128, 164, 197, 762, 731, 328, 105, 496, 934, 186,
        121, 627, 380, 721, 621, 997, 674, 212, 173, 592, 737, 370, 696, 189,
        917, 924, 616, 564, 96
    };

    for(int i = 0; i < 100; i++) {
        btree_insert(&btree, keys[i]);
    }

    oj_assert_eq_int(1, test_btree_node_values(btree.root, 1, 623));
    struct btree_node* l1n0 = btree_node_child_at_index(btree.root, 0);
    struct btree_node* l1n1 = btree_node_child_at_index(btree.root, 1);

    oj_assert_eq_int(1, test_btree_node_values(l1n0, 2, 200, 358));
    oj_assert_eq_int(1, test_btree_node_values(l1n1, 2, 762, 852));

    struct btree_node* l2n0 = btree_node_child_at_index(l1n0, 0);
    struct btree_node* l2n1 = btree_node_child_at_index(l1n0, 1);
    struct btree_node* l2n2 = btree_node_child_at_index(l1n0, 2);

    struct btree_node* l2n3 = btree_node_child_at_index(l1n1, 0);
    struct btree_node* l2n4 = btree_node_child_at_index(l1n1, 1);
    struct btree_node* l2n5 = btree_node_child_at_index(l1n1, 2);

    oj_assert_eq_int(1, test_btree_node_values(l2n0, 4, 70, 110, 156, 180));
    oj_assert_eq_int(1, test_btree_node_values(l2n1, 2, 267, 322));
    oj_assert_eq_int(1, test_btree_node_values(l2n2, 3, 429, 529, 600));
    oj_assert_eq_int(1, test_btree_node_values(l2n3, 2, 687, 715));
    oj_assert_eq_int(1, test_btree_node_values(l2n4, 2, 788, 808));
    oj_assert_eq_int(1, test_btree_node_values(l2n5, 2, 908, 963));

    oj_assert_eq_int(1, test_btree_node_values(btree_node_child_at_index(l2n0, 0), 3, 7, 25, 59));
    oj_assert_eq_int(1, test_btree_node_values(btree_node_child_at_index(l2n0, 1), 3, 81, 96, 105));
    oj_assert_eq_int(1, test_btree_node_values(btree_node_child_at_index(l2n0, 2), 3, 121, 128, 136));
    oj_assert_eq_int(1, test_btree_node_values(btree_node_child_at_index(l2n0, 3), 3, 157, 164, 173));
    oj_assert_eq_int(1, test_btree_node_values(btree_node_child_at_index(l2n0, 4), 5, 186, 187, 189, 191, 197));

    oj_assert_eq_int(1, test_btree_node_values(btree_node_child_at_index(l2n1, 0), 5, 203, 212, 216, 222, 253));
    oj_assert_eq_int(1, test_btree_node_values(btree_node_child_at_index(l2n1, 1), 3, 287, 309, 311));
    oj_assert_eq_int(1, test_btree_node_values(btree_node_child_at_index(l2n1, 2), 4, 322, 328, 333, 351));

    oj_assert_eq_int(1, test_btree_node_values(btree_node_child_at_index(l2n2, 0), 5, 370, 380, 382, 390, 401));
    oj_assert_eq_int(1, test_btree_node_values(btree_node_child_at_index(l2n2, 1), 5, 470, 488, 496, 498, 504));
    oj_assert_eq_int(1, test_btree_node_values(btree_node_child_at_index(l2n2, 2), 5, 561, 562, 564, 577, 592));
    oj_assert_eq_int(1, test_btree_node_values(btree_node_child_at_index(l2n2, 3), 4, 603, 616, 621, 622));

    oj_assert_eq_int(1, test_btree_node_values(btree_node_child_at_index(l2n3, 0), 4, 627, 661, 671, 674));
    oj_assert_eq_int(1, test_btree_node_values(btree_node_child_at_index(l2n3, 1), 3, 695, 696, 698));
    oj_assert_eq_int(1, test_btree_node_values(btree_node_child_at_index(l2n3, 2), 5, 721, 731, 737, 739, 746));

    oj_assert_eq_int(1, test_btree_node_values(btree_node_child_at_index(l2n4, 0), 2, 765, 778));
    oj_assert_eq_int(1, test_btree_node_values(btree_node_child_at_index(l2n4, 1), 2, 798, 802));
    oj_assert_eq_int(1, test_btree_node_values(btree_node_child_at_index(l2n4, 2), 5, 816, 824, 834, 843, 847));

    oj_assert_eq_int(1, test_btree_node_values(btree_node_child_at_index(l2n5, 0), 2, 881, 900));
    oj_assert_eq_int(1, test_btree_node_values(btree_node_child_at_index(l2n5, 1), 5, 917, 924, 934, 948, 963));
    oj_assert_eq_int(1, test_btree_node_values(btree_node_child_at_index(l2n5, 2), 4, 964, 968, 974, 997));

    // Level 0: 623
    // Level 1: 200 358
    // Level 1: 762 852
    //
    // Level 2: 70 110 156 180
    // Level 2: 267 322
    // Level 2: 429 529 600
    // Level 2: 687 715
    // Level 2: 788 808
    // Level 2: 908 963
    //
    // Level 3: 7 25 59
    // Level 3: 81 96 105
    // Level 3: 121 128 136
    // Level 3: 157 164 173
    // Level 3: 186 187 189 191 197
    //
    // Level 3: 203 212 216 222 253
    // Level 3: 287 309 311
    // Level 3: 322 328 333 351
    //
    // Level 3: 370 380 382 390 401
    // Level 3: 470 488 496 498 504
    // Level 3: 561 562 564 577 592
    // Level 3: 603 616 621 622
    //
    // Level 3: 627 661 671 674
    // Level 3: 695 696 698
    // Level 3: 721 731 737 739 746
    //
    // Level 3: 765 778
    // Level 3: 798 802
    // Level 3: 816 824 834 843 847
    //
    // Level 3: 881 900
    // Level 3: 917 924 934 948 963
    // Level 3: 964 968 974 997

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
    oj_run(test_btree_insert_100_random_keys);
    oj_run(test_btree_insert_100_keys_increasing_order);
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
