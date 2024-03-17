#include <stdlib.h>
#include <stdio.h>

#define MIN_DEQUE_SIZE 5

typedef struct circular_deque {
    int front;
    int rear;
    int size;
    int fill;
    float* A;
} CircularDeque;

CircularDeque* createCircularDeque() {
    CircularDeque* q = (CircularDeque*)malloc(sizeof(CircularDeque));
    q->A = (float*)malloc(sizeof(float)*MIN_DEQUE_SIZE);
    q->front = -1;
    q->rear = -1;
    q->fill = -1;
    q->size = MIN_DEQUE_SIZE;
    return q;
}

int resize(CircularDeque* q, int cap) {
    float* T = (float*)malloc(sizeof(float)*cap);
    for(int i = q->front+1; i < q->front+q->size+1; i++) { *(T+i-q->front-1) = *(q->A+i%q->size); }
    free(q->A);
    q->A = T;
    q->rear = q->size-1;
    q->front = -1;
    q->size = cap;
    return 0;
}

int push_back(CircularDeque* q, float x) {
    q->fill += 1;
    if(q->fill >= q->size) { resize(q, q->size*2); }
    q->rear = (q->rear + 1)%q->size;
    *(q->A + q->rear) = x;
    return 0;
}

int push_front(CircularDeque* q, float x) {
    q->fill += 1;
    if(q->fill >= q->size) { resize(q, q->size*2); }
    if(q->fill==0) {
        q->front = q->size-1;
        q->rear = 0;
        *(q->A) = x;
        return 0;
    }
    q->front = (q->front - 1)%q->size;
    *(q->A + q->front + 1) = x;
    return 0;
}

float pop_front(CircularDeque* q) {
    q->fill -= 1;
    if(q->fill < q->size/2 && q->size/2 > MIN_DEQUE_SIZE) { resize(q, q->size/2); }
    q->front = (q->front + 1)%q->size;
    return *(q->A+q->front);
}

float pop_back(CircularDeque* q) {
    q->fill -= 1;
    if(q->fill < q->size/2 && q->size/2 > MIN_DEQUE_SIZE) { resize(q, q->size/2); }
    q->rear = (q->rear - 1)%q->size;
    return *(q->A+q->rear);
}

int displayCircularDeque(CircularDeque* q) {
    int i;
    printf("\n[ ");
    for(i = 1; i<=q->fill; i++) { printf("%.2f, ", *(q->A+(q->front+i)%q->size)); }
    printf("%.2f ]\n", *(q->A+(q->front+i)%q->size));
    return 0;
}