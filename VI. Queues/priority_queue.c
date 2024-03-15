#include "../IV. Dynamic Arrays and Linked Lists/dynamic_array.c"

//In a priority queue, every i-th element is greater in value than every (2i+1)-th and (2i+2)th element.
//Whenever a new element is enqueued/dequeued, priority queue shall arrange itself so that the abovementioned rule is not broken.
//The process to arrange elements in this way is called Heapifying.

typedef struct priority_queue {
    DynamicArray* A;
} PriorityQueue;

PriorityQueue* createPriorityQueue() {
    PriorityQueue* q = (PriorityQueue*)malloc(sizeof(PriorityQueue));
    q->A = createDynamicArray();
    return q;
}