#include <stdlib.h>
#include <stdio.h>

typedef unsigned char uint8;
typedef signed char int8;

typedef struct circular_queue {
    uint8* array;
    uint8 max_len;
    uint8 len;
    int8 front;
    int8 rear;
} CircularQueue;

CircularQueue queue_new() {
    uint8* array = (uint8*)malloc(sizeof(uint8)*7);
    CircularQueue q = {array, 7, 0, 0, -1};
    return q;
}

uint8 get_moduloed_index(int8 x, uint8 s) {
    return (s+x)%s;
}

void queue_resize(CircularQueue* q, uint8 len) {
    uint8* array = (uint8*)malloc(sizeof(uint8)*len);

    for(uint8 i = 0; i < q->len; i++) { 
        array[i] = q->array[get_moduloed_index(q->rear+i+1, q->max_len)];
    }
    free(q->array);
    q->array = array;
    q->front = q->len;
    q->rear = -1;
    q->max_len = len;
}

void queue_push_front(CircularQueue* q, uint8 x) {
    if(q->len==q->max_len) { queue_resize(q, q->len*2); }
    q->array[get_moduloed_index(q->front, q->max_len)] = x;
    q->front = get_moduloed_index((q->front + 1), q->max_len);
    ++q->len;
}

uint8 queue_pop_rear(CircularQueue* q) {
    --q->len;
    int8 k = q->array[get_moduloed_index(q->rear+1, q->max_len)];
    q->rear = get_moduloed_index((q->rear + 1), q->max_len);
    return k;
}

void queue_push_rear(CircularQueue* q, uint8 x) {
    if(q->len==q->max_len) { queue_resize(q, q->len*2); }
    q->array[get_moduloed_index(q->rear, q->max_len)] = x;
    q->rear = get_moduloed_index((q->rear - 1), q->max_len);
    ++q->len;
}

uint8 queue_pop_front(CircularQueue* q) {
    --q->len;
    int8 k = q->array[get_moduloed_index(q->front-1, q->max_len)];
    q->front = get_moduloed_index((q->front - 1), q->max_len);
    return k;
}

void queue_print(CircularQueue* q) {
    printf("[ ");
    for(int i = q->rear; i < q->rear+q->len; i++) {
        printf("%d, ", (int)q->array[get_moduloed_index(i+1, q->max_len)]);
    }
    printf("]\n");
}

uint8 queue_is_empty(CircularQueue* q) {
    return q->len==0;
}

uint8 queue_front(CircularQueue* q) {
    return q->array[get_moduloed_index(q->front-1, q->max_len)];
}

uint8 queue_rear(CircularQueue* q) {
    return q->array[get_moduloed_index(q->rear+1, q->max_len)];
}

void queue_free(CircularQueue* q) { free(q->array); }