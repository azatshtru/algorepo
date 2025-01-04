#include "../headers/priority_queue.h"

void* priority_queue_allocate(uint32 type_size, int(*priority)(void*)) {
    struct priority_queue* q = malloc(sizeof(struct priority_queue));
    q->v = vec_allocate(VEC_INIT_SIZE, type_size);
    q->priority = priority;
    return (void*)q;
}

void priority_queue_free(void* q_ptr, void(*free_fn)(void*)) {
    struct priority_queue* q = (struct priority_queue*)q_ptr;
    vec_free(q->v, free_fn);
    free(q);
}

int priority_queue_len(void* q_ptr) {
    struct priority_queue* q = (struct priority_queue*)q_ptr;
    return vec_len(q->v);
}

int priority_queue_is_empty(void* q_ptr) {
    return priority_queue_len(q_ptr) == 0;
}
