#include <stdlib.h>

struct persistent_segtree_simple_sum_vertex {
    struct persistent_segtree_simple_sum_vertex* l;
    struct persistent_segtree_simple_sum_vertex* r;
    int sum;
};

struct persistent_segtree_simple_sum_vertex* persistent_segtree_simple_sum_vertex_from_value(int value) {
    struct persistent_segtree_simple_sum_vertex* v = malloc(sizeof(struct persistent_segtree_simple_sum_vertex));
    v->l = NULL;
    v->r = NULL;
    v->sum = value;
    return v;
}

struct persistent_segtree_simple_sum_vertex* persistent_segtree_simple_sum_vertex_from_branches(
    struct persistent_segtree_simple_sum_vertex* l,
    struct persistent_segtree_simple_sum_vertex* r
) {
    struct persistent_segtree_simple_sum_vertex* v = malloc(sizeof(struct persistent_segtree_simple_sum_vertex));
    v->sum = 0;
    v->l = l;
    v->r = r;
    if(l) { v->sum += l->sum; }
    if(r) { v->sum += r->sum; }
    return v;
}

struct persistent_segtree_simple_sum_vertex* persistent_segtree_simple_sum_build(int* a, int tl, int tr) {
    if (tl == tr) return persistent_segtree_simple_sum_vertex_from_value(a[tl]);
    int tm = (tl + tr) / 2;
    return persistent_segtree_simple_sum_vertex_from_branches(
        persistent_segtree_simple_sum_build(a, tl, tm), persistent_segtree_simple_sum_build(a, tm+1, tr)
    );
}

int persistent_segtree_simple_sum(struct persistent_segtree_simple_sum_vertex* v, int tl, int tr, int l, int r) {
    if (l > r) return 0;
    if (l == tl && tr == r) return v->sum;
    int tm = (tl + tr) / 2;
    return persistent_segtree_simple_sum(v->l, tl, tm, l, (r < tm ? r : tm))
         + persistent_segtree_simple_sum(v->r, tm+1, tr, (l > tm + 1 ? l : tm + 1), r);
}

struct persistent_segtree_simple_sum_vertex* persistent_segtree_simple_sum_update(
    struct persistent_segtree_simple_sum_vertex* v, int tl, int tr, int pos, int new_val
) {
    if (tl == tr) return persistent_segtree_simple_sum_vertex_from_value(new_val);
    int tm = (tl + tr) / 2;
    if (pos <= tm) {
        return persistent_segtree_simple_sum_vertex_from_branches(
            persistent_segtree_simple_sum_update(v->l, tl, tm, pos, new_val), v->r
        );
    } else {
        return persistent_segtree_simple_sum_vertex_from_branches(
            v->l, persistent_segtree_simple_sum_update(v->r, tm+1, tr, pos, new_val)
        );
    }
}

// persistent segment tree can be used to answer queries of the form "find the kth smallest element in range"
// by creating a persistent segtree over the histogram of the array

int main() {
    return 0;
}
