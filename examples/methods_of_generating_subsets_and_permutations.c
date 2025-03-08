#include "../headers/vector.h"
#include "../headers/array_utils.h"

void subsets_recursive(vector(int) subset, int k, int n) {
    if (k == n) {
        printf("subset!");
        array_print_primitive(vec_as_array(subset), vec_len(subset), "%d");
    } else {
        subsets_recursive(subset, k + 1, n);
        vec_push(subset, k);
        subsets_recursive(subset, k + 1, n);
        vec_pop(subset, -1);
    }
}

void subsets_bitwise(int n) {
    for(int i = 0; i < (1<<n); i++) {
        printf("subset![ ");
        for(int j = 0; j < n; j++) {
            if((1<<j)&i) { printf("%d, ", j); }
        }
        printf("\b\b ]\n");
    }
}

void permutations_recursive(vector(int) permutation, int* chosen, int n) {
    if (vec_len(permutation) == n) {
        printf("subset!");
        array_print_primitive(vec_as_array(permutation), vec_len(permutation), "%d");
    } else {
        for (int i = 0; i < n; i++) {
            if (chosen[i]) continue;
            chosen[i] = 1;
            vec_push(permutation, i);
            permutations_recursive(permutation, chosen, n);
            chosen[i] = 0;
            vec_pop(permutation, -1);
        }
    }
}

int main() {
    vector(int) subset = vec_new(int);
    vec_free(subset, NULL);
    return 0;
}
