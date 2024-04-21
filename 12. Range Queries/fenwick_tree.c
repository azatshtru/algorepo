#include <stdlib.h>

//Binary indexed tree with the property that every kth index contains the sum of elements in the range [k-p+1, k]
//where p is the largest power of 2 that divided k. p can be easily found with the bit operation k&-k.

//function to calculate the sum to k in O(log k)


int add(int k, int x, int len, int* tree) {
    while(k <= len) {
        tree[k] += x;
        k += k&-k;
    }
    return 0;
}

int* initializeFenwickTree(int len, int* A) {
    int* tree = (int*)malloc(sizeof(int)*(len+1));
    for(int i = 0; i < len+1; i++) { tree[i] = 0; }
    for(int i = 1; i < len+1; i++) { add(i, A[i-1], len+1, tree); }
    return tree;
}

int sum(int k, int* tree) {
    int s = 0;
    while(k >= 1) {
        s += tree[k];
        k -= k&-k; 
    }
    return s;
}

int sum_range(int len, int* A, int a, int b) {
    int* tree = initializeFenwickTree(len, A);
    int sum_a = sum(a, tree);
    int sum_b = sum(b+1, tree);
    free(tree);
    return sum_b-sum_a;
}