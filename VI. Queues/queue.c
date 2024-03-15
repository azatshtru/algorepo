#include "../IV. Dynamic Arrays and Linked Lists/dynamic_array.c"

typedef struct queue {
    DynamicArray* A;
} Queue;

Queue* createQueue() {
    Queue* q = (Queue*)malloc(sizeof(Queue));
    q->A = createDynamicArray();
    return q;
}

int nq(Queue* q, float x) {
    push(q->A, x);
    return 0;
}

float dq(Queue* q) {
    return pop(q->A, 0);
}