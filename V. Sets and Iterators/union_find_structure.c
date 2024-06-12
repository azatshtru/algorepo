#include <stdlib.h>

#ifndef UNION_FIND_STRUCTURE
#define UNION_FIND_STRUCTURE

typedef unsigned int uint32;
typedef signed int int32;
typedef unsigned char boolean;

typedef struct union_find_forest {
    uint32* link;
    uint32* size;
} DisjointSet;

DisjointSet disjoint_set_new(uint32* link, uint32* size, uint32 len) {
    for(int i = 0; i < len; i++) {
        link[i] = i;
        size[i] = 1;
    }
    DisjointSet ufs = { link, size };
    return ufs;
}

int32 disjoint_set_find_representative(DisjointSet set, int32 x) {
    while(x != set.link[x]) { x = set.link[x]; }
    return x;
}

#define ds_find_rep disjoint_set_find_representative

boolean disjoint_set_same_component(DisjointSet set, int32 a, int32 b) {
    return ds_find_rep(set, a) == ds_find_rep(set, b);
}

void disjoint_set_unite(DisjointSet* set_ptr, int32 a, int32 b) {
    DisjointSet set = *set_ptr;
    a = ds_find_rep(set, a);
    b = ds_find_rep(set, b);
    if(set.size[a] <= set.size[b]) {
        set_ptr->size[b] += set.size[a];
        set_ptr->link[a] = b;
    } else {
        set_ptr->size[a] += set.size[b];
        set_ptr->link[b] = a;
    }
}

#endif