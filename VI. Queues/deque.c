#include "../IV. Dynamic Arrays and Linked Lists/linked_list.c"

//pronounced "Deck"

typedef struct deque {
    LinkedList* A;
} Deque;

Deque* createDeque() {
    Deque* q = (Deque*)malloc(sizeof(Deque));
    q->A = createLinkedList();
    return q;
}

int push_front(Deque* q, float x) {
    push(q->A, x);
    return 0;
}

float pop_front(Deque* q) {
    return pop(q->A, q->A->size-1);
}

int push_back(Deque* q, float x) {
    insert(q->A, 0, x);
    return 0;
}

float pop_back(Deque* q) {
    return pop(q->A, 0);
}