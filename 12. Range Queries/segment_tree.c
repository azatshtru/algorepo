#include <stdlib.h>

//In a segment tree, every kth element is the given range query of (2k+1)th and (2k+2)th element.
//This works in O(log n)

int sum(int n, int* tree, int a, int b) {
    a += n; b += n;
    int s = 0;
    while(a <= b) {
        if(a%2==1) { s += tree[a++]; }
        if(b%2==0) { s += tree[b--]; }
        a /= 2; b /= 2;
    }
    return s;
} 

int add(int n, int* tree, int k, int x) {
    k += n;
    tree[k] += x;
    for(k /= 2; k >= 1; k /= 2) { tree[k] = tree[2*k] + tree[2*k+1]; }
    return 0;
}

int* initializeSumSegmentTree(int len, int* A) {
    int* tree = (int*)malloc(sizeof(int)*(len*2));
    for(int i = 0; i < len*2; i++) { tree[i] = 0; }
    for(int i = 0; i < len; i++) { add(len, tree, i, A[i]); }
    return tree;
}

int sum_range(int len, int* A, int a, int b) {
    int* tree = initializeSumSegmentTree(len, A);
    int s = sum(len, tree, a, b);
    free(tree);
    return s;
}
