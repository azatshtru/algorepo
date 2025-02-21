#include <stdlib.h>

#ifndef FENWICK_TREE
#define FENWICK_TREE

/// a binary indexed tree with the property that every kth index contains the sum of elements in the range [k - p + 1, k]
/// where p is the largest power of 2 that divides k
/// p can be easily found with the bit operation k&-k

/// add a value x at an index k and at the corresponding position in the fenwick tree
int fenwick_tree_add(int k, int x, int len, int* tree);

int* fenwick_tree_init(int len, int* array, int* tree);

/// calculate the sum to k in O(log k)
int fenwick_tree_sum_q(int k, int* tree);

int fenwick_tree_sum(int len, int* tree, int a, int b);

#endif
