#include "../headers/disjoint_set_int.h"

DisjointSetInt disjoint_set_int_new(int max_size) {
    DisjointSetInt set;
    set.parent = malloc(sizeof(int) * max_size);
    set.size = malloc(sizeof(int) * max_size);
    return set;
}

void disjoint_set_int_free(DisjointSetInt* set) {
    free(set->parent);
    free(set->size);
}

void disjoint_set_int_insert(DisjointSetInt* set, int v) {
    set->parent[v] = v;
    set->size[v] = 1;
}

int disjoint_set_int_find(DisjointSetInt* set, int v) {
    if(v == set->parent[v]) {
        return v;
    }
    return set->parent[v] = disjoint_set_int_find(set, set->parent[v]);    
}

int disjoint_set_int_union(DisjointSetInt* set, int a, int b) {
    a = disjoint_set_int_find(set, a);
    b = disjoint_set_int_find(set, b);
    if(a != b) {
        if(set->size[a] < set->size[b]) {
            a = a ^ b;
            b = a ^ b;
            a = a ^ b;
        }
        set->parent[b] = a;
        set->size[a] += set->size[b];
        return 1;
    }
    return 0;
}
