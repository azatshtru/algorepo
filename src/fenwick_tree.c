#include "../headers/fenwick_tree.h"

/// a binary indexed tree with the property that every kth index contains the sum of elements in the range [k - p + 1, k]
/// where p is the largest power of 2 that divides k
/// p can be easily found with the bit operation k&-k

/// add a value x at an index k and at the corresponding position in the fenwick tree
int fenwick_tree_add(int k, int x, int len, int* tree) {
    while(k <= len) {
        tree[k] += x;
        k += k&-k;
    }
    return 0;
}

int* fenwick_tree_init(int len, int* array, int* tree) {
    tree[0] = 0;
    for(int i = 1; i < len + 1; i++) {
        tree[i] = array[i];
    }
    for(int i = 1; i < len + 1; i++) {
        int parent = i + i&-i;
        if(parent <= len) {
            tree[parent] += tree[i];
        }
    }
    return tree;
}

/// calculate the sum to k in O(log k)
int fenwick_tree_sum_q(int k, int* tree) {
    int s = 0;
    while(k >= 1) {
        s += tree[k];
        k -= k&-k; 
    }
    return s;
}

int fenwick_tree_sum(int len, int* tree, int a, int b) {
    int sum_a = fenwick_tree_sum_q(a, tree);
    int sum_b = fenwick_tree_sum_q(b + 1, tree);
    return sum_b - sum_a;
}
