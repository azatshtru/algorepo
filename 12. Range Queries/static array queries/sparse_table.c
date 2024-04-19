#include <stdlib.h>

int logb2(int n) {
    int x = n;
    int log = 0;
    while(x > 1) { ++log; x/=2; }
    return log;
}
    
int pow_2(int x) {
    int res = 1;
    for(int i = 0; i < x; i++) { res *= 2; }
    return res;
}

int min(int a, int b) {
    return a > b ? b : a;
}

int min_q(int* A, int a, int b, int** P) {
    int w = (b-a+1)/2;
    int v;
    if(a==b) { v = A[a]; }
    else { v = min(min_q(A, a, a+w-1, P), min_q(A, a+w, b, P)); }
    P[logb2(b-a+1)][a] = v;
    return v;
}

int** generateMinSparseTable(int len, int* A) {
    int p = logb2(len);
    int** P = (int**)malloc((1+p)*sizeof(int*));
    for(int i = 0; i < p; i++) { P[i] = (int*)malloc(sizeof(int)*(len-pow_2(i)+1)); }
    return P;
}

int fillSparseTable(int** P, int len, int* A) {
    int p = logb2(len);
    for(int i = 0; i < p; i++) {
        for(int j = 0; j < len-pow_2(i)+1; j++) {
            min_q(A, j, j+pow_2(i)-1, P);
        }
    }
    for(int i = 0; i < p; i++) {
        for(int j = 0; j < len-pow_2(i)+1; j++) {
            printf("%d ", P[i][j]);
        }
        printf("\n");
    }
    return 0;
}

int releaseSparseTable(int** P, int length) {
    int p = logb2(length);
    for(int i = 0; i < p; i++) { free(P[i]); }
    free(P);
    return 0;
}

//O(1) minimum due to sparse table.
int calculateMin(int len, int* A, int a, int b) {
    int p = logb2(b-a+1);
    int k = pow_2(p);
    int** P = generateMinSparseTable(len, A);
    int x = min(min_q(A, a, a+k-1, P), min_q(A, b-k+1, b, P));
    releaseSparseTable(P, len);
    return x;
}