#include <stdio.h>
#include "../IV. Dynamic Arrays and Linked Lists/dynamic_array.c"

//The core-recursive-algorithm has two arrays, P and C, P stores the current permutation, C stores the chosen values.
//If a value is chosen, it is skipped over.
//After a value k is chosen, it is pushed to P and all the permutations of values not including k are performed and pushed to P, and processed accordingly.
//After that, the value k is unchosen, and popped from P.
//Processing step happens when the length of current permutation array P equals n

int permutations(int n) {
    static DynamicArray* P = NULL;
    static DynamicArray* C = NULL;
    if(P==NULL) { P = createDynamicArray(); }
    if(C==NULL) { C = createDynamicArray(); }

    if(P->fill+1 == n) {
        //process permutation
        printf("[ ");
        for(int i = 0; i <= P->fill; i++) { printf("%.2f ", *(P->array + i)); }
        printf("]\n");
    } else {
        //core algorithm
        for(int i = 0; i < n; i++) {
            if(*(C->array + i)) { continue; }
            *(C->array + i) = 1;
            push(P, i);
            permutations(n);
            *(C->array + i) = 0;
            pop(P, P->fill);
        }
    }
    return 0;
}