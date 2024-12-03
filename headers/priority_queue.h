#ifndef PRIORITY_QUEUE
#define PRIORITY_QUEUE

#include <stdlib.h>
#include "vector.h"

typedef struct priority_queue {
    Vector v;
    int(*priority)(void*);
} PriorityQueue;

PriorityQueue* priority_queue_allocate(uint32 type_size, int(*priority)(void*));
void priority_queue_dq(PriorityQueue* q);



#endif
