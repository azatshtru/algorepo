#include <stdlib.h>
#include "../headers/logging.h"

void quadratic_polynomial_lazy_update_segtree_shift_coeff(int* coeff, int shift) {
    coeff[2] += coeff[0] * shift * shift + coeff[1] * shift;
    coeff[1] += 2 * shift * coeff[0];
}

void quadratic_polynomial_lazy_update_segtree_first_natural_sums(int* sums, int n) {
    sums[0] = n * (n + 1) * (2 * n + 1) / 6;
    sums[1] = n * (n + 1) / 2;
    sums[2] = n;
}

struct quadratic_polynomial_lazy_update_segtree_vertex {
    int value;
    int lazy[3];
    int x;
    int y;
    struct quadratic_polynomial_lazy_update_segtree_vertex* left;
    struct quadratic_polynomial_lazy_update_segtree_vertex* right;
};

struct quadratic_polynomial_lazy_update_segtree_vertex* quadratic_polynomial_lazy_update_segtree_vertex_new(int value, int x, int y) {
    struct quadratic_polynomial_lazy_update_segtree_vertex* v = malloc(sizeof(struct quadratic_polynomial_lazy_update_segtree_vertex));
    v->value = value;
    v->lazy[0] = 0;
    v->lazy[1] = 0;
    v->lazy[2] = 0;
    v->left = NULL;
    v->right = NULL;
    v->x = x;
    v->y = y;
    return v;
}

struct quadratic_polynomial_lazy_update_segtree_vertex* quadratic_polynomial_lazy_update_segtree_build(int* array, int l, int r) {
    if(l == r) return quadratic_polynomial_lazy_update_segtree_vertex_new(array[l], l, r);
    int mid = (l + r) / 2;
    struct quadratic_polynomial_lazy_update_segtree_vertex* a = quadratic_polynomial_lazy_update_segtree_build(array, l, mid);
    struct quadratic_polynomial_lazy_update_segtree_vertex* b = quadratic_polynomial_lazy_update_segtree_build(array, mid + 1, r);
    struct quadratic_polynomial_lazy_update_segtree_vertex* v = quadratic_polynomial_lazy_update_segtree_vertex_new(a->value + b->value, l, r);
    v->left = a;
    v->right = b;
    return v;
}

void quadratic_polynomial_lazy_update_segtree_add_lazy(struct quadratic_polynomial_lazy_update_segtree_vertex* v, int a, int b, int c) {
    v->lazy[0] += a;
    v->lazy[1] += b;
    v->lazy[2] += c;
}

int quadratic_polynomial_lazy_update_segtree_sum(struct quadratic_polynomial_lazy_update_segtree_vertex* root, int a, int b) {
    int s[3];
    quadratic_polynomial_lazy_update_segtree_first_natural_sums(s, root->y - root->x + 1);
    if(a <= root->x && root->y <= b) return root->value + root->lazy[0] * s[0] + root->lazy[1] * s[1] + root->lazy[2] * s[2];
    if (b < root->x || a > root->y) return 0;

    root->value += root->lazy[0] * s[0] + root->lazy[1] * s[1] + root->lazy[2] * s[2];
    int shifted[3] = { root->lazy[0], root->lazy[1], root->lazy[1] };
    quadratic_polynomial_lazy_update_segtree_shift_coeff(shifted, root->right->x - a);

    quadratic_polynomial_lazy_update_segtree_add_lazy(root->left, root->lazy[0], root->lazy[1], root->lazy[2]);
    quadratic_polynomial_lazy_update_segtree_add_lazy(root->right, shifted[0], shifted[1], shifted[2]);
    quadratic_polynomial_lazy_update_segtree_add_lazy(root, 0, 0, 0);
    
    return quadratic_polynomial_lazy_update_segtree_sum(root->left, a, b) + quadratic_polynomial_lazy_update_segtree_sum(root->right, a, b);
}

void quadratic_polynomial_lazy_update_segtree_update(
    struct quadratic_polynomial_lazy_update_segtree_vertex* root,
    int c1, int c2, int c3, int a, int b
) {
    if(a <= root->x && root->y <= b) {
        root->lazy[0] = c1;
        root->lazy[1] = c2;
        root->lazy[2] = c3;
        return;
    }
    int max = root->x > a ? root->x : a;
    int min = root->y < b ? root->y : b;
    if (b < root->x || a > root->y) return;
    int s[3];
    quadratic_polynomial_lazy_update_segtree_first_natural_sums(s, min - max + 1);
    root->value += c1 * s[0] + c2 * s[1] + c3 * s[2];
    int shifted[3] = { c1, c2, c3 };
    quadratic_polynomial_lazy_update_segtree_shift_coeff(shifted, root->right->x - a);
    quadratic_polynomial_lazy_update_segtree_update(root->left, c1, c2, c3, a, b);
    quadratic_polynomial_lazy_update_segtree_update(root->right, shifted[0], shifted[1], shifted[2], a, b);
}

int main() {
    int sample[16] = { 5, 8, 6, 3, 2, 7, 2, 6, 7, 1, 7, 5, 6, 2, 3, 2 };
    struct quadratic_polynomial_lazy_update_segtree_vertex* root = quadratic_polynomial_lazy_update_segtree_build(sample, 0, 15);
    quadratic_polynomial_lazy_update_segtree_update(root, 0, 1, 1, 1, 4);
    int sample_sum_query = quadratic_polynomial_lazy_update_segtree_sum(root, 2, 5);
    return 0;
}

// can be extended to higher degrees dynamically by calculating polynomial shifts using taylor series.
