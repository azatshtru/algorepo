#include "miniqutils.h"

#ifndef SIMPLE_SEGMENT_TREE
#define SIMPLE_SEGMENT_TREE

int segment_tree_update_min(int* tree, int a, int b);
int segment_tree_update_sum(int* tree, int a, int b);

int segment_tree_sum_q(int n, int* tree, int a, int b);
int segment_tree_min_q(int n, int* tree, int a, int b);

int segment_tree_add(int n, int* tree, int k, int x, int(*update_fn)(int*, int, int));
int* segment_tree_init(int len, int* array, int* tree, int(*update_fn)(int*, int, int));

#endif
