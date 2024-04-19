#include <stdlib.h>
#include <stdio.h>

//pronounced "Deck"

typedef struct node {
    float value;
    struct node* next;
    struct node* prev;
} Node;

typedef struct deque {
    int size;
    Node* front;
    Node* back;
} Deque;

Deque* createDeque() {
    Deque* q = (Deque*)malloc(sizeof(Deque));
    q->size = 0;
    return q;
}

int push_front(Deque* q, float v) {
    Node* n = (Node*)malloc(sizeof(Node));
    n->value = v;
    if(q->size == 0) { q->front = q->back = n; }
    else {
        q->front->next = n;
        n->prev = q->front;
        q->front = n;
    }
    q->size += 1;
    return 0;
}

int push_back(Deque* q, float v) {
    Node* n = (Node*)malloc(sizeof(Node));
    n->value = v;
    if(q->size == 0) { q->front = q->back = n; }
    else {
        q->back->prev = n;
        n->next = q->back;
        q->back = n;
    }
    q->size += 1;
    return 0;
}

float pop_front(Deque* q) {
    float v = q->front->value;
    Node* temp = q->front;
    q->front = q->front->prev;
    free(temp);
    q->size -= 1;
    return v;
}

float pop_back(Deque* q) {
    float v = q->back->value;
    Node* temp = q->back;
    q->back = q->back->next;
    free(temp);
    q->size -= 1;
    return v;
}

float displayDeque(Deque* q) {
    if(q->size==0) { printf("\n[ ]\n"); return 0; }
    if(q->front == q->back) { printf("\n[ %.2f ]\n", q->back->value); return 0; }
    int i;
    Node* ni = q->back;
    printf("\n[ %.2f, ", q->back->value);
    for(i = 1; i < q->size-1; i++) { 
        ni = ni->next;
        printf("%.2f, ", ni->value); 
    }
    printf("%.2f ]\n", q->front->value);
    return 0;
}