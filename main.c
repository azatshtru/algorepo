#include <stdio.h>
#include "headers/btree.h"

int main() {

    BTree tree = btree_new(3);
    btree_insert(&tree, 977);
    btree_insert(&tree, 408);
    btree_insert(&tree, 849);
    btree_insert(&tree, 628);
    btree_insert(&tree, 276);
    btree_insert(&tree, 379);
    btree_insert(&tree, 500);
    btree_insert(&tree, 708);
    btree_insert(&tree, 5);
    btree_insert(&tree, 589);
    btree_insert(&tree, 788);
    btree_insert(&tree, 525);
    btree_insert(&tree, 132);
    btree_insert(&tree, 604);
    btree_insert(&tree, 675);
    btree_insert(&tree, 759);
    btree_insert(&tree, 575);
    btree_insert(&tree, 860);
    btree_insert(&tree, 740);
    btree_insert(&tree, 715);
    btree_insert(&tree, 184);
    btree_insert(&tree, 604);
    btree_insert(&tree, 29);

    btree_traverse_and_print_keys(&tree);
    
    return 0;
}
