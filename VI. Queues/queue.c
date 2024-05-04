#include "../IV. Dynamic Arrays and Linked Lists/linked_list.c"

typedef struct queue {
    LinkedList* A;
} Queue;

Queue* createQueue() {
    Queue* q = (Queue*)malloc(sizeof(Queue));
    q->A = createLinkedList();
    return q;
}

int nq(Queue* q, float x) {
    return push(q->A, x);
}

float dq(Queue* q) {
    Node* temp = q->A->head;
    q->A->head = q->A->head->next;
    float v = temp->value;
    free(temp);
    q->A->size -= 1;
    return v;
}

int displayQueue(Queue* q) {
    prettyPrint(q->A);
    return 0;
}

void queue_free(Queue* q) {
    linked_list_free(q->A);
    free(q);
}