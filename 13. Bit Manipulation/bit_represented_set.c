#include "popcount.c"
//This represents a set with 31 elements as a 4-byte integer

int set_init() { return 0; }
int set_add_element(int A, int x) { return A | (1<<x); }
int set_union(int A, int B) { return A | B; }
int set_intersection(int A, int B) { return A & B; }
int set_difference(int A, int B) { return A & (~B); }

int iterate_subsets0n(int A) {
    for(int i = 0; i < (1<<A); i++) {
        //process subset
        printf("%d ", i);
    }
}

int iterate_subsets0n_of_size(int A, int size) {
    for(int i = 0; i < (1<<A); i++) {
        if(parallel_popcount(i)==size) { 
            //process subset
            printf("%d ", i);
        }
    }
}

int specific_subsets(int A) {
    int b = 0;
    do {
        //process subset
        printf("%d ", b);
    } while(b=(b-A)&A);
}