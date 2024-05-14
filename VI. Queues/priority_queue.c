#include "../std/vec.c"

// In a priority queue, every i-th element is greater in value than every (2i+1)-th and (2i+2)th element.
// Whenever a new element is enqueued/dequeued, priority queue shall arrange itself so that the abovementioned rule is not broken.
// The process to arrange elements in this way is called Heapifying.

#ifndef PRIORITY_QUEUE
#define PRIORITY_QUEUE

typedef struct prioritized_type {
    int8 priority;
    void* value_ptr;
} Prioritized_T;

typedef Prioritized_T* PriorityQueue;

PriorityQueue priority_queue_new() {
    PriorityQueue q = __vec_new__(Prioritized_T);
    return q;
}

void prioritized_type_swap(Prioritized_T* a, Prioritized_T* b) {
    Prioritized_T temp = *a;
    *a = *b;
    *b = temp;
}

void prioritized_type_print(Prioritized_T prioritized_value) {
    printf("(%p: %d)", prioritized_value.value_ptr, prioritized_value.priority);
}

void priority_queue_nq(PriorityQueue q, void* value_ptr, int8 priority) {
    Prioritized_T x = { priority, value_ptr };
    __vec_push__(q, x);
    uint8 i = vec_len(q)-1;
    while(i > 0 && priority >= q[(i-1)/2].priority) {
        prioritized_type_swap(q+i, q+(i-1)/2);
        i = (i-1)/2;
    }
}

Prioritized_T priority_queue_dq(PriorityQueue q) {
    prioritized_type_swap(q+0, q + vec_len(q)-1);
    Prioritized_T popped_value = __vec_pop__(Prioritized_T, q, -1);
    
    uint8 i = 0;
    while(i < vec_len(q)) {
        uint8 k = i;
        if(2*i+1 < vec_len(q) && q[k].priority < q[2*i+1].priority) { k = 2*i+1; }
        if(2*i+2 < vec_len(q) && q[k].priority < q[2*i+2].priority) { k = 2*i+2; }
        if(k==i) { break; }
        prioritized_type_swap(q+i, q+k);
        i = k;
    }

    return popped_value;
}

void priority_queue_free(PriorityQueue q) {
    vec_free(q, NULL);
}

#endif