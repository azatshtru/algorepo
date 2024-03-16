#include <stdlib.h>
#include <stdio.h>

//pronounced "Deck"

#define MIN_DEQUE_SIZE = 5;

typedef struct deque {
    int front;
    int rear;
    int size;
    int fill;
    float* A;
} Deque;

Deque* createDeque() {
    Deque* q = (Deque*)malloc(sizeof(Deque));
    q->A = (float*)malloc(sizeof(float)*5);
    q->front = -1;
    q->rear = -1;
    q->fill = -1;
    q->size = 5;
    return q;
}

int resize(Deque* q, int cap) {
    float* T = (float*)malloc(sizeof(float)*cap);
    for(int i = q->front+1; i < q->front+q->size+1; i++) { *(T+i-q->front-1) = *(q->A+i%q->size); }
    free(q->A);
    q->A = T;
    q->rear = q->size-1;
    q->front = -1;
    q->size = cap;
    return 0;
}

int push_back(Deque* q, float x) {
    q->fill += 1;
    if(q->fill >= q->size) { resize(q, q->size*2); }
    q->rear = (q->rear + 1)%q->size;
    *(q->A + q->rear) = x;
    return 0;
}

int push_front(Deque* q, float x) {
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

float pop_front(Deque* q) {
    q->fill -= 1;
    if(q->fill < q->size/2 && q->size/2 > 5) { resize(q, q->size/2); }
    q->front = (q->front + 1)%q->size;
    return *(q->A+q->front);
}

float pop_back(Deque* q) {
    q->fill -= 1;
    if(q->fill < q->size/2 && q->size/2 > 5) { resize(q, q->size/2); }
    q->rear = (q->rear - 1)%q->size;
    return *(q->A+q->rear);
}

int displayQueue(Deque* q) {
    int i;
    printf("\n[ ");
    for(i = 1; i<=q->fill; i++) { printf("%.2f, ", *(q->A+(q->front+i)%q->size)); }
    printf("%.2f ]\n", *(q->A+(q->front+i)%q->size));
    return 0;
}