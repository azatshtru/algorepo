#ifndef PRIORITY_QUEUE
#define PRIORITY_QUEUE

#include <stdlib.h>
#include "vector.h"
#include "miniqutils.h"

struct priority_queue {
    Vector* v;
    int(*priority)(void*);
    vector(int) proxy_priority;
};

void* priority_queue_allocate(uint32 type_size, int(*priority)(void*));
void priority_queue_free(void* q_ptr, void(*free_fn)(void*));
int priority_queue_len(void* q_ptr);
int priority_queue_is_empty(void* q_ptr);

int priority_queue_cmp_by_index(struct priority_queue* q, int i, int j);
void priority_queue_heapify(void* q_ptr);
int priority_queue_priority(void* q_ptr, int index);
void priority_queue_swap(void* q_ptr, int a, int b);

#define PriorityQueue(type) vector(type)*
#define priority_queue_new(type, priority) priority_queue_allocate(sizeof(type), priority)
#define priority_queue_get(q_ptr, index) (**(q_ptr))[(index)]

#define priority_queue_proxy_push(qptr, value, priority)                    \
do {                                                                        \
    vec_push(*(qptr), (value));                                             \
    vec_push(((struct priority_queue*)(qptr))->proxy_priority, priority);   \
} while(0)

#define priority_queue_nq(q_ptr, value)                                 \
do {                                                                    \
    **(*(q_ptr)+1) = (value);                                           \
    struct priority_queue* __q__ = (struct priority_queue*)(q_ptr);     \
    int priority = __q__->priority(*(*(q_ptr)+1));                      \
    priority_queue_proxy_push((q_ptr), (value), 0);                    \
    int i = priority_queue_len(q_ptr)-1;                                \
    while(i > 0 && priority <= __q__->priority(**(q_ptr) + (i-1)/2)) {  \
        priority_queue_swap((q_ptr), i, (i-1)/2);                       \
        i = (i-1)/2;                                                    \
    }                                                                   \
} while(0)

#define priority_queue_nqx(q_ptr, value, priority)                          \
do {                                                                        \
    **(*(q_ptr)+1) = (value);                                               \
    struct priority_queue* __q__ = (struct priority_queue*)(q_ptr);         \
    priority_queue_proxy_push((q_ptr), (value), 0);                        \
    int i = priority_queue_len(q_ptr)-1;                                    \
    while(i > 0 && priority <= priority_queue_priority(__q__, (i-1)/2)) {   \
        priority_queue_swap((q_ptr), i, (i-1)/2);                           \
        i = (i-1)/2;                                                        \
    }                                                                       \
} while(0)

#define priority_queue_dq(q_ptr) (                                  \
     **(*(q_ptr)+1) = ***(q_ptr),                                   \
     priority_queue_swap((q_ptr), 0, priority_queue_len(q_ptr) - 1),\
     vec_zap(*(q_ptr), -1, NULL),                                   \
     priority_queue_heapify(q_ptr),                                 \
     **(*(q_ptr)+1)                                                 \
     )


#endif
