#include <stdio.h>
#include "orange_juice.h"
#include "../headers/vector.h"

oj_test(test_vec_cmp_returns_true_for_same_vectors) {
    vector(int) v1 = vec_new(int);
    vector(int) v2 = vec_new(int);

    vec_push(v1, 5);
    vec_push(v1, 85);
    vec_push(v1, 9);
    vec_push(v1, 89);
    vec_push(v1, 58);

    vec_push(v2, 5);
    vec_push(v2, 85);
    vec_push(v2, 9);
    vec_push(v2, 89);
    vec_push(v2, 58);

    int cmp = vec_cmp(v1, v2);

    vec_free(v1, NULL);
    vec_free(v2, NULL);

    oj_assert_eq_int(1, cmp);

    oj_fresh;
}

oj_test(test_vec_cmp_returns_false_for_different_vectors) {
    vector(int) v1 = vec_new(int);
    vector(int) v2 = vec_new(int);

    vec_push(v1, 72);
    vec_push(v1, 73);
    vec_push(v1, 87);
    vec_push(v1, 41);
    vec_push(v1, 61);

    vec_push(v2, 5);
    vec_push(v2, 85);
    vec_push(v2, 9);
    vec_push(v2, 89);
    vec_push(v2, 58);

    int cmp = vec_cmp(v1, v2);

    vec_free(v1, NULL);
    vec_free(v2, NULL);

    oj_assert_eq_int(0, cmp);

    oj_fresh;
}

oj_test(test_vec_cmp_returns_false_for_different_length_vectors) {
    vector(int) v1 = vec_new(int);
    vector(int) v2 = vec_new(int);

    vec_push(v1, 5);
    vec_push(v1, 85);
    vec_push(v1, 9);
    vec_push(v1, 89);

    vec_push(v2, 5);
    vec_push(v2, 85);
    vec_push(v2, 9);
    vec_push(v2, 89);
    vec_push(v2, 58);

    int cmp = vec_cmp(v1, v2);
    vec_free(v1, NULL);
    vec_free(v2, NULL);
    oj_assert_eq_int(0, cmp);

    oj_fresh;
}

oj_test(vec_index_returns_index_of_element) {
    vector(int) v = vec_new(int);
    vec_push(v, 73);
    vec_push(v, 87);
    vec_push(v, 41);
    vec_push(v, 61);
    vec_push(v, 27);
    oj_assert_eq_int(3, vec_index(v, 61));
    oj_assert_eq_int(2, vec_index(v, 41));
    oj_assert_eq_int(0, vec_index(v, 73));
    oj_fresh;
}

oj_test(vec_contains_returns_true_if_element_is_present) {
    vector(int) v = vec_new(int);
    vec_push(v, 73);
    vec_push(v, 87);
    vec_push(v, 41);
    vec_push(v, 61);
    vec_push(v, 27);
    oj_assert_eq_int(1, vec_contains(v, 61));
    oj_assert_eq_int(0, vec_contains(v, 31));
    oj_assert_eq_int(1, vec_contains(v, 73));
    oj_fresh;
}

oj_prepare(vector_index_tests) {
    oj_run(vec_index_returns_index_of_element);
    oj_run(vec_contains_returns_true_if_element_is_present);
    oj_report;
    oj_fresh;
}

oj_prepare(vector_equality_tests) {
    oj_run(test_vec_cmp_returns_true_for_same_vectors);
    oj_run(test_vec_cmp_returns_false_for_different_vectors);
    oj_run(test_vec_cmp_returns_false_for_different_length_vectors);

    oj_report;
    oj_fresh;
}

int main() {
    oj_blend(vector_equality_tests, 0);
    oj_blend(vector_index_tests, 0);
    return 0;
}
