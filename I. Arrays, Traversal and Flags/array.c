#include <stdio.h>
#include <stdlib.h>

//Perhaps the most simple data structure of them all is the humble array.
//Some space is allocated on the heap, the first location stores the length of the array. 
//The subsequent locations store the values of the array.
float* Array(int size) {
    float* p = (float*)malloc(sizeof(float)*(size+1));
    for(int i = 1; i < size+1; i++) {
        *(p+i) = 0;
    }
    *p = size;
    return p;
}

float get(float* A, int i) {
    return *(A+i+1);
}

int set(float* A, int i, float x) {
    *(A+i+1) = x;
    return 0;
}

int len(float* A) {
    return *A;
}

int prettyPrint(float* A) {
    int i;
    printf("\n[ ");
    for(i = 0; i < *A-1; i++) {
        printf("%.2f, ", get(A, i));
    }
    printf("%.2f ]\n", get(A, i));
    return 0;
}

int clear(float* A) {
    free(A);
    return 0;
}