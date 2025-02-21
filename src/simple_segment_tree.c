#include "../headers/simple_segment_tree.h"

// in a segment tree, every kth element stores the range query of (2k+1)th and (2k+2)th element
// queries take O(log n) time
// simple segment trees can support sum, min, max, xor, and, or

int segment_tree_update_min(int* tree, int a, int b) {
    return min_i(2, tree[a], tree[b]);
}

int segment_tree_update_sum(int* tree, int a, int b) {
    return tree[a] + tree[b];
}

int segment_tree_sum_q(int n, int* tree, int a, int b) {
    a += n; b += n;
    int s = 0;
    while(a <= b) {
        if(a%2==1) { s += tree[a++]; }
        if(b%2==0) { s += tree[b--]; }
        a /= 2; b /= 2;
    }
    return s;
}

int segment_tree_min_q(int n, int* tree, int a, int b) {
    a += n; b += b;
    int s = I32_MAX;
    while(a <= b) {
        if(a % 2 == 1) { s = min_i(2, s, tree[a++]); }
        if(b % 2 == 0) { s = min_i(2, s, tree[b--]); }
        a /= 2; b/= 2;
    }
    return s;
}

int segment_tree_add(int n, int* tree, int k, int x, int(*update_fn)(int*, int, int)) {
    k += n;
    tree[k] += x;
    for(k /= 2; k >= 1; k /= 2) {
        tree[k] = update_fn(tree, 2 * k, 2 * k + 1);
    }
    return 0;
}

int* segment_tree_init(int len, int* array, int* tree, int(*update_fn)(int*, int, int)) {
    for(int i = 0; i < len * 2; i++) {
        tree[i] = 0;
    }
    for(int i = 0; i < len; i++) {
        segment_tree_add(len, tree, i, array[i], update_fn);
    }
    return tree;
}
