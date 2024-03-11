#include "../IV. Dynamic Arrays and Linked Lists/dynamic_array.c"

typedef struct iterator {
    float* begin;
    float* p;
    float* end;
} Iterator;

Iterator* init_iter(DynamicArray* A) {
    float* c = (float*)malloc(A->fill*sizeof(float));
    for(int i = 0; i < A->fill+1; i++) { *(c+i) = *(A->array+i); }
    Iterator* iter = (Iterator*)malloc(sizeof(Iterator));
    iter->begin = c;
    iter->p = c;
    iter->end = c + A->fill;
    return iter;
}

float consume(Iterator* iter) {
    float v = *(iter->p);
    if(iter->p == iter->end) { 
        free(iter->begin); 
        free(iter);
    } else {
        iter->p += 1;
    }
    return v;
}

