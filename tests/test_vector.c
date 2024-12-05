#include <stdio.h>
#include "testutils.h"
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

oj_prepare(vector_equality_tests) {
    oj_run(test_vec_cmp_returns_true_for_same_vectors);
    oj_run(test_vec_cmp_returns_false_for_different_vectors);
    oj_run(test_vec_cmp_returns_false_for_different_length_vectors);

    oj_report;
    oj_fresh;
}

int main() {
    oj_blend(vector_equality_tests, 0);
    return 0;
}
