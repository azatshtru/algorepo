#include <stdlib.h>

#define stdVector(TYPE) typedef struct vector_##TYPE {\
int size;\
int fill;\
TYPE * array;\
} Vector_##TYPE;\
Vector_##TYPE * createVector_##TYPE () {\
    Vector_##TYPE * P = (Vector_##TYPE *)malloc(sizeof(Vector_##TYPE));\
    P->size = 5;\
    P->fill = -1;\
    TYPE * A = (TYPE *)malloc(sizeof(TYPE)*P->size);\
    P->array = A;\
    return P;\
}\
TYPE get_vector##TYPE (Vector_##TYPE * P, int i) {\
    return *(P->array + i);\
}\
int push_vector##TYPE (Vector_##TYPE * P, TYPE x) {\
    P->fill += 1;\
    if(P->fill >= P->size) {\
        P->size *= 2;\
        TYPE * A = (TYPE *)malloc(sizeof(TYPE)*P->size);\
        int i;\
        for (i = 0; i < P->fill; i++){ *(A+i)=*(P->array+i); }\
        free(P->array);\
        P->array = A;\
    }\
    *(P->array+P->fill)=x;\
    return 0;\
}\
TYPE pop_vector##TYPE (Vector_##TYPE * P, int i) {\
    TYPE v = *(P->array+i);\
    P->fill -= 1;\
    for (int j = i; j < P->fill+1; j++){ *(P->array+j)=*(P->array+j+1); }\
    if(P->fill < P->size/2 && P->size/2 > 5) {\
        P->size /= 2;\
        TYPE * A = (TYPE *)malloc(sizeof(TYPE)*P->size);\
        int k;\
        for (k = 0; k < P->fill+1; k++){ *(A+k)=*(P->array+k); }\
        free(P->array);\
        P->array = A;\
    }\
    return v;\
} \
int insert_vector##TYPE (Vector_##TYPE * P, int i, TYPE x) {\
    if(i > P->fill) {\
        push_vector##TYPE(P, x);\
        return 0;\
    }\
    push_vector##TYPE(P, x);\
    for (int j = P->fill+1; j > i; j--){\
        *(P->array+j)=*(P->array+j-1);\
    }\
    *(P->array+i) = x;\
    return 0;\
}\

#define Vector(TYPE) Vector_##TYPE *
#define createVector(TYPE) createVector_##TYPE()
#define get(TYPE, P, i) get_vector##TYPE (P, i)
#define push(TYPE, P, x) push_vector##TYPE(P, x)
#define pop(TYPE, P, i) pop_vector##TYPE(P, i)
#define insert(TYPE, P, i, x) insert_vector##TYPE(P, i, x)