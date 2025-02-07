#include <math.h>
#include "../IV. Dynamic Arrays and Linked Lists/dynamic_array.c"

//A O(2^n) search can be performed in O(2^(n/2)) by splitting the search input into two, performing separate searches on both parts and combining the result meaningfully.

//As an example, take the problem of calculating the number of subsets of a set such that the elements of the subset sum to a certain 'k'.

int constructSubsets(DynamicArray** AA, DynamicArray* A, int p, int qreset) {
    static DynamicArray* S = NULL;
    if(S == NULL) { S = createDynamicArray(); }
    static int q = 0;
    if(!qreset) { q = 0; }

    if(p==0) { 
        for(int i = 0; i <= S->fill; i++) { push(*(AA+q), *(A->array + (int)*(S->array+i) - 1)); }
        q++;
    }
    else {
        push(S, p);
        constructSubsets(AA, A, p-1, 1);
        pop(S, S->fill);
        constructSubsets(AA, A, p-1, 1);
    }
    return 0;
}

DynamicArray** setOfSubsets(DynamicArray* A) {
    DynamicArray** AA = (DynamicArray**)malloc(sizeof(DynamicArray*) * pow(2, A->fill+1));
    for(int i = 0; i < pow(2, A->fill+1); i++) { *(AA+i) = createDynamicArray(); }
    constructSubsets(AA, A, A->fill+1, 0);
    return AA;
} 

int printSubsets(DynamicArray** S, int n) {
    for(int i = 0; i < pow(2, n); i++) { prettyPrint(*(S+i)); }
    return 0;
}

float sumOfArray(DynamicArray* A) {
    int sum = 0;
    for(int i = 0; i < A->fill+1; i++) { sum += *(A->array + i); }
    return sum;
}

//This algorithm divides the array into two, calculates subset sums for each in O(2^(n/2)) and then iterates through each of them in O(n^2) to calculate final result.
int ksum_subsets(DynamicArray* A, int k) {
    int middle = (A->fill+1)/2;
    DynamicArray* P = createDynamicArray();
    DynamicArray* Q = createDynamicArray();
    for(int i = 0; i < middle; i++) { push(P, *(A->array+i)); }
    for(int i = middle; i < A->fill+1; i++) { push(Q, *(A->array+i)); }
    DynamicArray** PP = setOfSubsets(P);
    DynamicArray** QQ = setOfSubsets(Q);
    free(P->array);
    free(Q->array);
    free(P);
    free(Q);
    DynamicArray* M = createDynamicArray();
    DynamicArray* N = createDynamicArray();

    for(int i = 0; i < pow(2, middle); i++) { push(M, sumOfArray(*(PP+i))); }
    for(int i = 0; i < pow(2, A->fill-middle+1); i++) { push(N, sumOfArray(*(QQ+i))); }
    int count = 0;
    for(int i = 0; i < M->fill+1; i++) {
        for(int j = 0; j < N->fill+1; j++) {
            count += *(M->array + i) + *(N->array + j) == k;
        }
    }

    return count;
}