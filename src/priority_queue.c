#include "../headers/priority_queue.h"

void* priority_queue_allocate(uint32 type_size, int(*priority)(void*)) {
    PriorityQueue* q = malloc(sizeof(PriorityQueue));
    q->v = vec_allocate(VEC_INIT_SIZE, type_size);
    q->priority = priority;
    return q;
}
