#include "../headers/priority_queue.h"

void* priority_queue_allocate(uint32 type_size, int(*priority)(void*)) {
    struct priority_queue* q = malloc(sizeof(struct priority_queue));
    q->v = vec_allocate(VEC_INIT_SIZE, type_size);
    q->priority = priority;
    q->proxy_priority = vec_new(int);
    return (void*)q;
}

void priority_queue_free(void* q_ptr, void(*free_fn)(void*)) {
    struct priority_queue* q = (struct priority_queue*)q_ptr;
    vec_free(q->v, free_fn);
    vec_free(q->proxy_priority, NULL);
    free(q);
}

int priority_queue_len(void* q_ptr) {
    struct priority_queue* q = (struct priority_queue*)q_ptr;
    return vec_len(q->v);
}

int priority_queue_is_empty(void* q_ptr) {
    return priority_queue_len(q_ptr) == 0;
}

int priority_queue_priority(void* q_ptr, int index) {
    struct priority_queue* q = (struct priority_queue*)q_ptr;
    if(q->priority == NULL) {
        return vec_get(q->proxy_priority, index);
    }
    return q->priority(q->v->data + index*q->v->type_size);
}

int priority_queue_cmp_by_index(struct priority_queue* q, int i, int j) {
    int typesize = q->v->type_size;
    return i < priority_queue_len(q) && j < priority_queue_len(q)
        && priority_queue_priority(q, i) < priority_queue_priority(q, j);
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
        priority_queue_swap(q_ptr, i, j);
        i = j;
    }
}

void priority_queue_swap(void* q_ptr, int a, int b) {
    struct priority_queue* q = (struct priority_queue*)q_ptr;
    int typesize = q->v->type_size;
    swap(q->v->data + a*typesize, q->v->data + b*typesize, typesize);
    swap(*q->proxy_priority + a, *q->proxy_priority + b, sizeof(int));
}
