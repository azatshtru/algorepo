#include "../IV. Dynamic Arrays and Linked Lists/dynamic_array.c"

typedef struct deque {
    DynamicArray* A;
} Deque;

Deque* createDeque() {
    Deque* q = (Deque*)malloc(sizeof(Deque));
    q->A = createDynamicArray();
    return q;
}

int push_front(Deque* q, float x) {
    push(q->A, x);
    return 0;
}

float pop_front(Deque* q) {
    return pop(q->A, q->A->fill);
}

int push_back(Deque* q, float x) {
    insert(q->A, 0, x);
    return 0;
}

float pop_back(Deque* q) {
    return pop(q->A, 0);
}