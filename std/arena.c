#include <stdlib.h>

#define stdArena(TYPE)\
typedef struct arena_##TYPE {\
    int length;\
    TYPE * current;\
    TYPE * start;\
} Arena##TYPE;\
Arena##TYPE arena_alloc_##TYPE (int size) {\
    Arena##TYPE A;\
    A.length = size;\
    A.current = A.start = (TYPE *)malloc(sizeof(TYPE)*size);\
    return A;\
}\


//TODO: complete this


