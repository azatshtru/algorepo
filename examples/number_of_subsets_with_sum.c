// some O(2^n) search can be performed in O(2^(n/2)) by splitting the search space into two parts,
// then performing separate searches on both parts and combining the results meaningfully, this is called Meet in the Middle

#include "../headers/complete_search.h"
#include "../headers/sorting.h"
#include "../headers/binary_search.h"

// given an array of n numbers, in how many ways can a subset be chosen such that the sum of subset is x

float number_of_subsets_with_sum_int_cmp(void* x, void* y) {
    return *(int*)x - *(int*)y;
}

int number_of_subsets_with_sum(int len, int* array, int x) {
    int count = 0;
    int l1 = len/2;
    int l2 = len - l1;
    vector(int) subset = vec_new(int);

    vector(int) s1 = vec_new(int);
    vector(int) s2 = vec_new(int);
    vec_push(s1, 0);
    vec_push(s2, 0);

    while(subset_next(subset, l1 - 1)) {
        int sum = 0;
        for(int i = 0; i < vec_len(subset); i++) {
            sum += array[vec_get(subset, i)];
        }
        vec_push(s1, sum);
    }

    vec_clear(subset);

    while(subset_next(subset, l2 - 1)) {
        int sum = 0;
        for(int i = 0; i < vec_len(subset); i++) {
            sum += array[l1 + vec_get(subset, i)];
        }
        vec_push(s2, sum);
    }

    quicksort(vec_as_array(s1), sizeof(int), 0, vec_len(s1) - 1, number_of_subsets_with_sum_int_cmp);
    quicksort(vec_as_array(s2), sizeof(int), 0, vec_len(s2) - 1, number_of_subsets_with_sum_int_cmp);
    
    for(int i = 0; i < vec_len(s1); i++) {
        int value = x - vec_get(s1, i);
        int j = binary_search_l(vec_as_array(s2), sizeof(int), vec_len(s2), &value, number_of_subsets_with_sum_int_cmp);
        count += vec_get(s1, i) + vec_get(s2, j) == x;
    }

    vec_free(subset, NULL);
    vec_free(s1, NULL);
    vec_free(s2, NULL);
    return count;
}

int main() {
    int array[5] = { 2, 4, 5, 9, 1 };
    int count = number_of_subsets_with_sum(5, array, 15);
    return 0;
}
