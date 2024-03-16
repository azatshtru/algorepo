#include <stdlib.h>
#include <stdio.h>

typedef struct queue {
    int front;
    int rear;
    int size;
    int fill;
    float* A;
} Queue;

Queue* createQueue() {
    Queue* q = (Queue*)malloc(sizeof(Queue));
    q->A = (float*)malloc(sizeof(float)*5);
    q->front = -1;
    q->rear = -1;
    q->fill = -1;
    q->size = 5;
    return q;
}

int resize(Queue* q, int cap) {
    float* T = (float*)malloc(sizeof(float)*cap);
    for(int i = q->front+1; i < q->front+q->size+1; i++) { *(T+i-q->front-1) = *(q->A+i%q->size); }
    free(q->A);
    q->A = T;
    q->rear = q->size-1;
    q->front = -1;
    q->size = cap;
    return 0;
}

int nq(Queue* q, float x) {
    q->fill += 1;
    if(q->fill >= q->size) { resize(q, q->size*2); }
    q->rear = (q->rear + 1)%q->size;
    *(q->A + q->rear) = x;
    return 0;
}

float dq(Queue* q) {
    q->fill -= 1;
    if(q->fill < q->size/2 && q->size/2 > 5) { resize(q, q->size/2); }
    q->front = (q->front + 1)%q->size;
    return *(q->A+q->front);
}

int displayQueue(Queue* q) {
    int i;
    printf("\n[ ");
    for(i = 1; i<=q->fill; i++) { printf("%.2f, ", *(q->A+(q->front+i)%q->size)); }
    printf("%.2f ]\n", *(q->A+(q->front+i)%q->size));
    return 0;
}