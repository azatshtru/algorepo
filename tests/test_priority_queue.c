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
    PriorityQueue(int) pq = priority_queue_new(int, int_identity);
    priority_queue_nq(pq, 42);
    int result = priority_queue_get(pq, 0);
    oj_assert_eq_int(42, result);
    priority_queue_free(pq, NULL);
    oj_fresh;
}

oj_prepare(priority_queue_setup_tests) {
    oj_run(priority_queue_allocation);
    oj_run(priority_queue_is_empty_when_nothing_is_pushed);
    oj_report;
    oj_fresh;
}

oj_prepare(priority_queue_io_tests) {
    oj_run(priority_queue_enqueue_42);
    oj_report;
    oj_fresh;
}


int main() {
    oj_blend(priority_queue_setup_tests, 0);
    oj_blend(priority_queue_io_tests, 0);
    return 0;
}
