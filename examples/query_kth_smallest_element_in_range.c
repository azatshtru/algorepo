#include "../headers/vector.h"

struct kth_smallest_element_in_range_segtree_vertex {
    struct kth_smallest_element_in_range_segtree_vertex* l;
    struct kth_smallest_element_in_range_segtree_vertex* r;
    int sum;
};

struct kth_smallest_element_in_range_segtree_vertex* kth_smallest_element_in_range_vertex_from_value(int value) {
    struct kth_smallest_element_in_range_segtree_vertex* v = malloc(sizeof(struct kth_smallest_element_in_range_segtree_vertex));
    v->l = NULL;
    v->r = NULL;
    v->sum = value;
    return v;
}

struct kth_smallest_element_in_range_segtree_vertex* kth_smallest_element_in_range_vertex_from_branches(
    struct kth_smallest_element_in_range_segtree_vertex* l,
    struct kth_smallest_element_in_range_segtree_vertex* r
) {
    struct kth_smallest_element_in_range_segtree_vertex* v = malloc(sizeof(struct kth_smallest_element_in_range_segtree_vertex));
    v->sum = 0;
    v->l = l;
    v->r = r;
    if(l) { v->sum += l->sum; }
    if(r) { v->sum += r->sum; }
    return v;
}

struct kth_smallest_element_in_range_segtree_vertex* kth_smallest_element_in_range_segtree_build(int tl, int tr) {
    if (tl == tr) return kth_smallest_element_in_range_vertex_from_value(0);
    int tm = (tl + tr) / 2;
    return kth_smallest_element_in_range_vertex_from_branches(
        kth_smallest_element_in_range_segtree_build(tl, tm),
        kth_smallest_element_in_range_segtree_build(tm+1, tr)
    );
}

struct kth_smallest_element_in_range_segtree_vertex* kth_smallest_element_in_range_segtree_update(
    struct kth_smallest_element_in_range_segtree_vertex* v, int tl, int tr, int pos
) {
    if (tl == tr) return kth_smallest_element_in_range_vertex_from_value(v->sum+1);
    int tm = (tl + tr) / 2;
    if (pos <= tm) {
        return kth_smallest_element_in_range_vertex_from_branches(
            kth_smallest_element_in_range_segtree_update(v->l, tl, tm, pos), v->r
        );
    } else {
        return kth_smallest_element_in_range_vertex_from_branches(
            v->l, kth_smallest_element_in_range_segtree_update(v->r, tm+1, tr, pos)
        );
    }
}

int kth_smallest_element_in_range_segtree_find_kth(struct kth_smallest_element_in_range_segtree_vertex* vl,
             struct kth_smallest_element_in_range_segtree_vertex *vr,
             int tl, int tr, int k
             ) {
    if (tl == tr) return tl;
    int tm = (tl + tr) / 2, left_count = vr->l->sum - vl->l->sum;
    if (left_count >= k) return kth_smallest_element_in_range_segtree_find_kth(vl->l, vr->l, tl, tm, k);
    return kth_smallest_element_in_range_segtree_find_kth(vl->r, vr->r, tm+1, tr, k-left_count);
}

void kth_smallest_element_in_range_roots(int len, int* a, vector(struct kth_smallest_element_in_range_segtree_vertex*) roots, int max_value) {
    int tl = 0;
    int tr = max_value + 1;
    vec_push(roots, kth_smallest_element_in_range_segtree_build(tl, tr));
    for (int i = 0; i < len; i++) {
        vec_push(roots, kth_smallest_element_in_range_segtree_update(vec_get(roots, vec_len(roots) - 1), tl, tr, a[i]));
    }
}

int kth_smallest_element_in_range(int len, vector(struct kth_smallest_element_in_range_segtree_vertex*) roots, int max_value, int a, int b, int k) {
    int result = kth_smallest_element_in_range_segtree_find_kth(
        vec_get(roots, a), vec_get(roots, b), 0, max_value + 1, k
    );
    return result;
}
