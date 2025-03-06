#include <stdlib.h>
#include "../headers/hashset.h"
#include "../headers/logging.h"

struct element_count_in_range_int2int_map {
    int k;
    int v;
};

unsigned int element_count_in_range_int2int_hash(void* x) {
    int primes[10] = { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29 };
    unsigned int hash = 0;
    int n = ((struct element_count_in_range_int2int_map*)x)->k;
    for(int i = 0; i < 10; i++) {
        hash += (n * primes[i]) % (i + 1);
    }
    return hash;
}

int element_count_in_range_int2int_cmp(void* x, void* y) {
    return ((struct element_count_in_range_int2int_map*)x)->k
        == ((struct element_count_in_range_int2int_map*)y)->k;
}

struct element_count_in_range_segtree_vertex {
    hashset(struct element_count_in_range_int2int_map) value;
    int x;
    int y;
    struct element_count_in_range_segtree_vertex* left;
    struct element_count_in_range_segtree_vertex* right;
};

struct element_count_in_range_segtree_vertex* element_count_in_range_segtree_vertex_new(int x, int y) {
    struct element_count_in_range_segtree_vertex* v = malloc(sizeof(struct element_count_in_range_segtree_vertex));
    v->value = hashset_new(struct element_count_in_range_int2int_map, element_count_in_range_int2int_hash, element_count_in_range_int2int_cmp);
    v->left = NULL;
    v->right = NULL;
    v->x = x;
    v->y = y;
    return v;
}

void element_count_in_range_merge_int2int_maps(
    hashset(struct element_count_in_range_int2int_map) a,
    hashset(struct element_count_in_range_int2int_map) b
) {
    int j = 0;
    for(int i = 0; i < hashset_len(b); i++) {
        j = hashset_lazy_iterate(b, j);
        struct element_count_in_range_int2int_map value = (*b)[j];
        if(hashset_contains(a, value)) {
            value.v += hashset_get(a, value).v;
        }
        hashset_insert(a, value);
    }
}

struct element_count_in_range_segtree_vertex* element_count_in_range_segtree_build(int* array, int l, int r) {
    if(l == r) {
        struct element_count_in_range_segtree_vertex* v = element_count_in_range_segtree_vertex_new(l, r);
        struct element_count_in_range_int2int_map value = { array[l], 1 };
        hashset_insert(v->value, value);
        return v;
    }
    int mid = (l + r) / 2;
    struct element_count_in_range_segtree_vertex* a = element_count_in_range_segtree_build(array, l, mid);
    struct element_count_in_range_segtree_vertex* b = element_count_in_range_segtree_build(array, mid + 1, r);
    struct element_count_in_range_segtree_vertex* v = element_count_in_range_segtree_vertex_new(l, r);
    v->left = a;
    v->right = b;
    element_count_in_range_merge_int2int_maps(v->value, a->value); 
    element_count_in_range_merge_int2int_maps(v->value, b->value); 
    return v;
}

int element_count_in_range_segtree_query(struct element_count_in_range_segtree_vertex* root, int a, int b, int k) {
    struct element_count_in_range_int2int_map query = { k, 0 };
    if(a <= root->x && root->y <= b) return hashset_get(root->value, query).v;
    if (b < root->x || a > root->y) return 0;

    return element_count_in_range_segtree_query(root->left, a, b, k) + element_count_in_range_segtree_query(root->right, a, b, k);
}

int main() {
    int sample[8] = { 3, 1, 2, 3, 1, 1, 1, 2 };
    struct element_count_in_range_segtree_vertex* root = element_count_in_range_segtree_build(sample, 0, 7);
    log_int("root hashmap length", hashset_len(root->value));
    log_int("query 1 in range (1, 5)", element_count_in_range_segtree_query(root, 1, 5, 1));
    log_int("query 3 in range (0, 5)", element_count_in_range_segtree_query(root, 0, 5, 3));
    return 0;
}
