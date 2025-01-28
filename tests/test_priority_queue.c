#include "../headers/priority_queue.h"
#include "orange_juice.h"

oj_test(priority_queue_allocation) {
    PriorityQueue(int) q = priority_queue_new(int);
    oj_assert(q != NULL, "priority queue didn't allocate properly");
    oj_assert(((struct priority_queue*)q)->data != NULL, "priority queue data didn't allocate properly");
    oj_assert(((struct priority_queue*)q)->tmp != NULL, "priority queue tmp didn't allocate properly");
    oj_assert(((struct priority_queue*)q)->priority != NULL, "priority priority data didn't allocate properly");
    priority_queue_free(q, NULL);
    oj_fresh;
}

oj_test(priority_queue_is_empty_when_nothing_is_pushed) {
    PriorityQueue(int) q = priority_queue_new(int);
    oj_assert_eq_int(0, priority_queue_len(q));
    oj_assert_eq_int(1, priority_queue_is_empty(q));
    priority_queue_free(q, NULL);
    oj_fresh;
}

oj_test(priority_queue_enqueue_42) {
    PriorityQueue(int) q = priority_queue_new(int);
    priority_queue_nq(q, 42, 42);
    int result = priority_queue_get(q, 0);
    oj_assert_eq_int(42, result);
    priority_queue_free(q, NULL);
    oj_fresh;
}

oj_test(priority_queue_enqueue_42_67_13) {
    PriorityQueue(int) q = priority_queue_new(int);
    priority_queue_nq(q, 42, 42);
    priority_queue_nq(q, 67, 67);
    priority_queue_nq(q, 13, 13);
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
    PriorityQueue(int) q = priority_queue_new(int);
    priority_queue_nq(q, 42, 42);
    priority_queue_nq(q, 67, 67);
    priority_queue_nq(q, 13, 13);
    priority_queue_nq(q, 109, 109);
    priority_queue_nq(q, 11, 11);
    oj_assert_eq_int(11, priority_queue_get(q, 0));
    oj_assert_eq_int(13, priority_queue_get(q, 1));
    oj_assert_eq_int(42, priority_queue_get(q, 2));
    oj_assert_eq_int(109, priority_queue_get(q, 3));
    oj_assert_eq_int(67, priority_queue_get(q, 4));
    priority_queue_free(q, NULL);
    oj_fresh;
}

oj_test(priority_queue_dequeue_once) {
    PriorityQueue(int) q = priority_queue_new(int);
    priority_queue_nq(q, 42, 42);
    priority_queue_nq(q, 67, 67);
    priority_queue_nq(q, 13, 13);
    priority_queue_nq(q, 109, 109);
    priority_queue_nq(q, 11, 11);

    int result = priority_queue_dq(q);
    oj_assert_eq_int(11, result);
    priority_queue_free(q, NULL);
    oj_fresh;
}

oj_test(priority_queue_dequeue_fivefold) {
    PriorityQueue(int) q = priority_queue_new(int);
    priority_queue_nq(q, 42, 42);
    priority_queue_nq(q, 67, 67);
    priority_queue_nq(q, 13, 13);
    priority_queue_nq(q, 109, 109);
    priority_queue_nq(q, 11, 11);
    oj_assert_eq_int(11, priority_queue_dq(q));
    oj_assert_eq_int(13, priority_queue_dq(q));
    oj_assert_eq_int(42, priority_queue_dq(q));
    oj_assert_eq_int(67, priority_queue_dq(q));
    oj_assert_eq_int(109, priority_queue_dq(q));

    priority_queue_free(q, NULL);

    oj_fresh;
}

oj_test(priority_queue_dequeue_two_things_and_enqueue_their_sum_until_one_thing_remains) {
    PriorityQueue(int) q = priority_queue_new(int);
    priority_queue_nq(q, 42, 42);
    priority_queue_nq(q, 67, 67);
    priority_queue_nq(q, 13, 13);
    priority_queue_nq(q, 109, 109);
    priority_queue_nq(q, 11, 11);
    priority_queue_nq(q, 51, 51);
    while(priority_queue_len(q) > 1) {
        int a = priority_queue_dq(q);
        int b = priority_queue_dq(q);
        priority_queue_nq(q, a+b, a+b);
    }

    int result = priority_queue_min(q);
    priority_queue_free(q, NULL);

    oj_assert_eq_int(293, result);
    oj_fresh;
}

struct test_huffman_tree_node {
    char symbol;
    int is_leaf;
    int frequency;

    struct test_huffman_tree_node* left;
    struct test_huffman_tree_node* right;
};

int test_huffman_tree_node_priority(void* node) {
    return (*((struct test_huffman_tree_node**)node))->frequency;
}

oj_test(priority_queue_enqueue_10_pointers) {
    struct test_huffman_tree_node* nodes[6];
    char character[6] = { ' ', 'A', 'B', 'C', 'D', 'E' };
    int frequencies[6] = { 10, 11, 6, 2, 10, 7 };

    PriorityQueue(struct test_huffman_tree_node*) tree = priority_queue_new(struct test_huffman_tree_node*);

    for(int i = 0; i < 6; i++) {
        nodes[i] = malloc(sizeof(struct test_huffman_tree_node));
        (*nodes[i]).symbol = character[i];
        (*nodes[i]).is_leaf = 1;
        (*nodes[i]).frequency = frequencies[i];
        (*nodes[i]).left = NULL;
        (*nodes[i]).right = NULL;
        priority_queue_nq(tree, nodes[i], frequencies[i]);
    }

    oj_assert_eq_pointer(nodes[3], priority_queue_get(tree, 0));
    oj_assert_eq_pointer(nodes[2], priority_queue_get(tree, 1));
    oj_assert_eq_pointer(nodes[5], priority_queue_get(tree, 2));
    oj_assert_eq_pointer(nodes[1], priority_queue_get(tree, 3));
    oj_assert_eq_pointer(nodes[4], priority_queue_get(tree, 4));
    oj_assert_eq_pointer(nodes[0], priority_queue_get(tree, 5));

    priority_queue_free(tree, NULL);

    for(int i = 0; i < 6; i++) {
        free(nodes[i]);
    }

    oj_fresh;
}

oj_prepare(priority_queue_setup_tests) {
    oj_run(priority_queue_allocation);
    oj_run(priority_queue_is_empty_when_nothing_is_pushed);
    oj_report;
    oj_fresh;
}

oj_prepare(priority_queue_internal_tests) {
    oj_report;
    oj_fresh;
}

oj_prepare(priority_queue_io_tests) {
    oj_run(priority_queue_enqueue_42);
    oj_run(priority_queue_enqueue_42_67_13);
    oj_run(priority_queue_enqueue_42_67_13_109_11);
    oj_run(priority_queue_dequeue_once);
    oj_run(priority_queue_dequeue_fivefold);
    oj_run(priority_queue_dequeue_two_things_and_enqueue_their_sum_until_one_thing_remains);
    oj_run(priority_queue_enqueue_10_pointers);
    oj_report;
    oj_fresh;
}


int main() {
    oj_blend(priority_queue_setup_tests, 0);
    oj_blend(priority_queue_io_tests, 0);
    oj_blend(priority_queue_internal_tests, 0);
    return 0;
}
