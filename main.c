#include <stdio.h>
#include "headers/btree.h"
#include "headers/red_black_tree.h"

int main() {
    RedBlackTree tree = red_black_tree_new(); 
    int testkeys[100] = {
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
        red_black_tree_insert(&tree, testkeys[i]);
    }

    red_black_tree_levelwise_traverse_and_print_keys(&tree);

    int deletelist[10] = {110, 852, 197, 105, 616, 674, 216, 380, 311, 7};

    for(int i = 0; i < 10; i++) {
        red_black_tree_delete(&tree, deletelist[i]);
    }

    printf("\n");
    red_black_tree_levelwise_traverse_and_print_keys(&tree);

    return 0;
}
