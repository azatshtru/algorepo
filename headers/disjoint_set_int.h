#include <stdlib.h>

#ifndef DISJOINT_SET_INT
#define DISJOINT_SET_INT

typedef struct disjoint_set_int {
    int* parent;
    int* size;
} DisjointSetInt;

DisjointSetInt disjoint_set_int_new(int max_size);
void disjoint_set_int_free(DisjointSetInt* set);
void disjoint_set_int_insert(DisjointSetInt* set, int v);
int disjoint_set_int_find(DisjointSetInt* set, int v);
int disjoint_set_int_union(DisjointSetInt* set, int a, int b);

#endif
