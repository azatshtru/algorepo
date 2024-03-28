#include <stdio.h>
#include "../IV. Dynamic Arrays and Linked Lists/dynamic_array.c"

//The standard elegant algorithm to find all subsets of the set of first n positive integers has a core-recursive-algorithm, and a processing stage.
//An integer n is used to keep track of when to perform processing stage during recursion, once n becomes zero, the subset is processed.
//The core algorithm is pretty simple, it has 4 steps: Push, Search, Pop, Search [PSPS]
//n is pushed into an array S, and then subsets of set of first n-1 integers are found, this gives all subsets of set of first n-1 positive integers that also include n.
//n is popped from the array S, and then subsets of set of first n-1 integers are found again, this gives all subsets of set of first n-1 positive integers not including n.

int subsets(int n) {
    //bookkeeping
    static DynamicArray* S = NULL;
    if(S==NULL) { S=createDynamicArray(); }

    if(n==0) {
        //process subset
        printf("[ ");
        for(int i = 0; i <= S->fill; i++) { printf("%.2f ", *(S->array + i)-1); }
        printf("]\n");
    } else {
        //core algorithm
        push(S, n);
        subsets(n-1);
        pop(S, S->fill);
        subsets(n-1);
    }
    return 0;
}

//Once the subsets of the set of first n positive integers are found, they can be used on an array as its indices to perform complete search.
int subsets1(DynamicArray* A, int n) {
    //bookkeeping
    static DynamicArray* S = NULL;
    if(S==NULL) { S=createDynamicArray(); }
    if(n==-1) { n = A->fill+1; }

    if(n==0) {
        //process subset
        printf("[ ");
        for(int i = 0; i <= S->fill; i++) { printf("%.2f ", *(A->array + (int)*(S->array + i) - 1)); }
        printf("]\n");
    } else {
        //core algorithm
        push(S, n);
        subsets1(A, n-1);
        pop(S, S->fill);
        subsets1(A, n-1);
    }
    return 0;
}

//Another way to find the subsets of first n positive integers is finding the binary representations of all numbers till 2^n.
//1<<n means the nth power of two.
int bsubsets(int n) {
    for(int i = 0; i < (1<<n); i++) {
        printf("[ ");
        for(int j = 0; j < n; j++) {
            if((1<<j)&i) { printf("%d ", j); }
        }
        printf("]\n");
    }
    return 0;
}