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

int priority_queue_cmp_by_index(struct priority_queue* q, int i, int j) {
    int typesize = q->v->type_size;
    return i < priority_queue_len(q) && j < priority_queue_len(q)
        && q->priority(q->v->data + i*typesize) < q->priority(q->v->data + j*typesize);
}

void priority_queue_heapify(void* q_ptr) {
    struct priority_queue* q = (struct priority_queue*)q_ptr;
    int typesize = q->v->type_size;

    int i = 0;
    while(2*i+1 < priority_queue_len(q)) {
    int j = i;
        if(priority_queue_cmp_by_index(q, 2*i+1, j)) { j = 2*i+1; }
        if(priority_queue_cmp_by_index(q, 2*i+2, j)) { j = 2*i+2; }
        if(j == i) { return; }
        swap(q->v->data + i*typesize, q->v->data + j*typesize, typesize);
        i = j;
    }
}
