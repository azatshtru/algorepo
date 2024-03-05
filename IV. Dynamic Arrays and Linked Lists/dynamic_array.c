#include <stdio.h>
#include <stdlib.h>

typedef struct dynamic_array {
    int size;
    int fill;
    float* array;
} DynamicArray;

DynamicArray* Dynamic_Array() {
    DynamicArray* P = (DynamicArray*)malloc(sizeof(DynamicArray));
    P->size = 5;
    P->fill = -1;
    float* A = (float*)malloc(sizeof(float)*P->size);
    for (int i = 0; i < 5; i++){ *(A+i)=0; }
    P->array = A;
    return P;
}

int push(DynamicArray* P, float x) {
    P->fill += 1;
    if(P->fill >= P->size) {
        P->size *= 2;
        float* A = (float*)malloc(sizeof(float)*P->size);
        int i;
        for (i = 0; i < P->fill; i++){ *(A+i)=*(P->array+i); }
        for (; i < P->size; i++){ *(A+i)=0; }
    }
    *(P->array+P->fill)=x;
    return 0;
}

float pop(DynamicArray* P, int i) {
    float v = *(P->array+i);
    P->fill -= 1;
    for (int j = i; j < P->fill+1; j++){ *(P->array+j)=*(P->array+j+1); }
    if(P->fill < P->size/2 && P->size > 5) {
        P->size /= 2;
        float* A = (float*)malloc(sizeof(float)*P->size);
        int k;
        for (k = 0; k < P->fill; k++){ *(A+k)=*(P->array+k); }
    }
    return v;
}

int insert(DynamicArray* P, int i, float x) {
    push(P, 0);
    for (int j = P->fill+1; j > i; j--){ 
        *(P->array+j)=*(P->array+j-1); 
    }
    *(P->array+i) = x;
    return 0;
}

int prettyPrint(DynamicArray* P) {
    int i;
    printf("\n[ ");
    for(i = 0; i < P->fill; i++) {
        printf("%.2f, ", *(P->array+i));
    }
    printf("%.2f ]\n", *(P->array+i));
    return 0;
}