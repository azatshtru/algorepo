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

int swap(float* a, float* b) {
    float temp = *a;
    *a = *b;
    *b = temp;
    return 0;
}

int nq(PriorityQueue* q, float x) {
    push(q->A, x);
    int i = q->A->fill;
    while(x >= *(q->A->array+(i-1)/2) && i > 0) {
        *(q->A->array+i) = *(q->A->array+(i-1)/2);
        *(q->A->array+(i-1)/2) = x;
        i = (i-1)/2;
    }
    return 0;
}

float dq(PriorityQueue* q) {
    swap(q->A->array, q->A->array + q->A->fill);
    float v = pop(q->A, q->A->fill);
    
    int i = 0;
    while(2*i+1 <= q->A->fill) {
        int max_index;
        if(2*i+2 > q->A->fill) { max_index = 2*i+1; }
        else { max_index = *(q->A->array + 2*i+1) > *(q->A->array + 2*i+2) ? 2*i+1 : 2*i+2; }
        if(*(q->A->array + max_index) > *(q->A->array + i)) { swap(q->A->array + max_index, q->A->array + i); }
        i = max_index;
    }
    return v;
}