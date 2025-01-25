#include <stdio.h>
#include "headers/btree.h"

int main() {
    BTree tree = btree_new(3); 
    btree_insert(&tree, 220);
    btree_insert(&tree, 314);
    btree_insert(&tree, 617);
    btree_insert(&tree, 355);
    btree_insert(&tree, 580);
    btree_insert(&tree, 871);

    btree_insert(&tree, 295);
    btree_insert(&tree, 71);
    btree_insert(&tree, 8);
    btree_insert(&tree, 332);
    btree_insert(&tree, 98);
    btree_insert(&tree, 87);
    btree_insert(&tree, 2871);

    BTree sree = btree_new(3);
    for(int i = 0; i < 1000; i++) {
        btree_insert(&sree, i);
    }
    btree_traverse_and_print_keys(&sree);
    return 0;
}
