#include <stdio.h>
#include "headers/btree.h"

int main() {
    BTree tree = btree_new(3);
    btree_insert(&tree, 1);
    btree_insert(&tree, 2);
    btree_insert(&tree, 3);
    btree_insert(&tree, 4);
    btree_insert(&tree, 5);
    btree_insert(&tree, 6);
    btree_insert(&tree, 7);
    btree_insert(&tree, 8);
    btree_insert(&tree, 9);
    btree_insert(&tree, 10);
    btree_insert(&tree, 11);
    btree_insert(&tree, 12);
    btree_traverse_and_print_keys(&tree);
    return 0;
}
