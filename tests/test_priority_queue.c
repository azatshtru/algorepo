#include "../headers/priority_queue.h"
#include "orange_juice.h"

int int_identity(void* x) {
    return *((int*)x);
}

oj_test(priority_queue_allocation) {
    PriorityQueue(int) q = priority_queue_new(int, int_identity);
    oj_assert(q != NULL, "priority queue didn't allocate properly");
    oj_assert(((struct priority_queue*)q)->v != NULL, "vector didn't allocate properly");
    priority_queue_free(q, NULL);
    oj_fresh;
}

oj_test(priority_queue_is_empty_when_nothing_is_pushed) {
    PriorityQueue(int) q = priority_queue_new(int, int_identity);
    oj_assert_eq_int(0, priority_queue_len(q));
    oj_assert_eq_int(1, priority_queue_is_empty(q));
    priority_queue_free(q, NULL);
    oj_fresh;
}

oj_test(priority_queue_enqueue_42) {
    PriorityQueue(int) q = priority_queue_new(int, int_identity);
    priority_queue_nq(q, 42);
    int result = priority_queue_get(q, 0);
    oj_assert_eq_int(42, result);
    priority_queue_free(q, NULL);
    oj_fresh;
}

oj_test(priority_queue_enqueue_42_67_13) {
    PriorityQueue(int) q = priority_queue_new(int, int_identity);
    priority_queue_nq(q, 42);
    priority_queue_nq(q, 67);
    priority_queue_nq(q, 13);
    int result0 = priority_queue_get(q, 0);
    int result1 = priority_queue_get(q, 1);
    int result2 = priority_queue_get(q, 2);
    oj_assert_eq_int(13, result0);
    oj_assert_eq_int(67, result1);
    oj_assert_eq_int(42, result2);
    priority_queue_free(q, NULL);
    oj_fresh;
}

oj_test(priority_queue_enqueue_42_67_13_109_11) {
    PriorityQueue(int) q = priority_queue_new(int, int_identity);
    priority_queue_nq(q, 42);
    priority_queue_nq(q, 67);
    priority_queue_nq(q, 13);
    priority_queue_nq(q, 109);
    priority_queue_nq(q, 11);
    oj_assert_eq_int(11, priority_queue_get(q, 0));
    oj_assert_eq_int(13, priority_queue_get(q, 1));
    oj_assert_eq_int(42, priority_queue_get(q, 2));
    oj_assert_eq_int(109, priority_queue_get(q, 3));
    oj_assert_eq_int(67, priority_queue_get(q, 4));
    priority_queue_free(q, NULL);
    oj_fresh;
}

oj_test(priority_queue_dequeue_once) {
    PriorityQueue(int) q = priority_queue_new(int, int_identity);
    priority_queue_nq(q, 42);
    priority_queue_nq(q, 67);
    priority_queue_nq(q, 13);
    priority_queue_nq(q, 109);
    priority_queue_nq(q, 11);
    // int result = priority_queue_dq(q) == 11;
    oj_assert_eq_int(11, priority_queue_dq(q));
    priority_queue_free(q, NULL);
    oj_fresh;
}

oj_test(priority_queue_dequeue_thrice) {
    PriorityQueue(int) q = priority_queue_new(int, int_identity);
    priority_queue_nq(q, 42);
    priority_queue_nq(q, 67);
    priority_queue_nq(q, 13);
    priority_queue_nq(q, 109);
    priority_queue_nq(q, 11);
    int result0 = priority_queue_dq(q);
    int result1 = priority_queue_dq(q);
    oj_assert_eq_int(11, result0);
    oj_assert_eq_int(13, result1);
    oj_assert_eq_int(42, priority_queue_dq(q));
    priority_queue_free(q, NULL);
    oj_fresh;
}

oj_test(priority_queue_heapify_109_13_67_42_11) {
    PriorityQueue(int) q = priority_queue_new(int, int_identity);
    vec_push(*q, 109);
    vec_push(*q, 13);
    vec_push(*q, 42);
    vec_push(*q, 67);
    vec_push(*q, 11);
    priority_queue_heapify(q);
    oj_assert_eq_int(13, priority_queue_get(q, 0));
    oj_assert_eq_int(11, priority_queue_get(q, 1));
    oj_assert_eq_int(42, priority_queue_get(q, 2));
    oj_assert_eq_int(67, priority_queue_get(q, 3));
    oj_assert_eq_int(109, priority_queue_get(q, 4));
    priority_queue_free(q, NULL);
    oj_fresh;
}

oj_test(priority_queue_cmp_two_indices) {
    PriorityQueue(int) q = priority_queue_new(int, int_identity);
    priority_queue_nq(q, 42);
    priority_queue_nq(q, 67);
    priority_queue_nq(q, 13);
    priority_queue_nq(q, 109);
    priority_queue_nq(q, 11);
    int result0 = priority_queue_cmp_by_index((struct priority_queue*)q, 0, 3);
    int result1 = priority_queue_cmp_by_index((struct priority_queue*)q, 4, 1);
    priority_queue_free(q, NULL);

    oj_assert_eq_int(1, result0);
    oj_assert_eq_int(0, result1);
    oj_fresh;
}

oj_prepare(priority_queue_setup_tests) {
    oj_run(priority_queue_allocation);
    oj_run(priority_queue_is_empty_when_nothing_is_pushed);
    oj_report;
    oj_fresh;
}

oj_prepare(priority_queue_internal_tests) {
    oj_run(priority_queue_heapify_109_13_67_42_11);
    oj_run(priority_queue_cmp_two_indices);
    oj_report;
    oj_fresh;
}

oj_prepare(priority_queue_io_tests) {
    oj_run(priority_queue_enqueue_42);
    oj_run(priority_queue_enqueue_42_67_13);
    oj_run(priority_queue_enqueue_42_67_13_109_11);
    oj_run(priority_queue_dequeue_once);
    oj_run(priority_queue_dequeue_thrice);
    oj_report;
    oj_fresh;
}


int main() {
    oj_blend(priority_queue_setup_tests, 0);
    oj_blend(priority_queue_io_tests, 0);
    oj_blend(priority_queue_internal_tests, 0);
    return 0;
}
