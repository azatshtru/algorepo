#ifndef PRIORITY_QUEUE
#define PRIORITY_QUEUE

#include <stdlib.h>
#include "vector.h"
#include "miniqutils.h"

struct priority_queue {
    Vector* v;
    int(*priority)(void*);
};

void* priority_queue_allocate(uint32 type_size, int(*priority)(void*));
void priority_queue_free(void* q_ptr, void(*free_fn)(void*));
int priority_queue_len(void* q_ptr);
int priority_queue_is_empty(void* q_ptr);

void priority_queue_dq(struct priority_queue* q);

#define PriorityQueue(type) vector(type)*
#define priority_queue_new(type, priority) priority_queue_allocate(sizeof(type), priority)

#define priority_queue_nq(q_ptr, value)                                 \
do {                                                                    \
    **(*(q_ptr)+2) = (value);                                           \
    struct priority_queue* q = (struct priority_queue*)q_ptr;           \
    int priority = q->priority((*(q_ptr)+2));                                \
    vec_push(*q_ptr, (value));                                          \
    int i = priority_queue_len(q_ptr)-1;                                    \
    while(i > 0 && priority >= q->priority(*q_ptr + (i-1)/2)) { \
        swap(**q_ptr+i, **q_ptr+(i-1)/2, sizeof(int));                  \
        i = (i-1)/2;                                                    \
    }                                                                   \
} while(0)

#endif
