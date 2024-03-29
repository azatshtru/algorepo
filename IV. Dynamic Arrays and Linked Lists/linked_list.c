#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    float value;
    struct node* next;
} Node;

typedef struct linkedList {
    int size;
    Node* head;
    Node* tail;
} LinkedList;

LinkedList* createLinkedList() {
    LinkedList* L = (LinkedList*)malloc(sizeof(LinkedList));
    L->size = 0;
    return L;
}

int push(LinkedList* A, float v) {
    Node* n = (Node*)malloc(sizeof(Node));
    n->value = v;
    if(A->size == 0) {
        A->head = n;
    } else if(A->size == 1) {
        A->tail = n;
        A->head->next = A->tail;
    } else {
        A->tail->next = n;
        A->tail = A->tail->next;
    }
    A->size += 1;
    return 0;
}

float pop(LinkedList* A, int i) {
    Node* temp;
    if(i==0){
        temp = A->head;
        A->head = A->head->next;
    } else {
        Node* ni = A->head;
        for(int j = 0; j < i-1; j++) { ni = ni->next; }
        temp = ni->next;
        if(i==A->size-1) {
            A->tail = ni;
        } else {
            ni->next = ni->next->next;
        }
    }
    float v = temp->value;
    free(temp);
    A->size -= 1;
    return v;
}

int insert(LinkedList* A, int i, float v) {
    Node* n = (Node*)malloc(sizeof(Node));
    n->value = v;
    if(i == A->size) {
        return push(A, v);
    } else if(i==0) {
        n->next = A->head;
        if(A->size==1){
            A->tail = A->head;
        }
        A->head = n;
    } else {
        Node* ni = A->head;
        for(int j = 0; j < i-1; j++) { ni = ni->next; }
        n->next = ni->next;
        ni->next = n;
    }
    A->size += 1;
    return 0;
}

int prettyPrint(LinkedList* A) {
    printf("\n[");
    Node* currentNode = A->head;
    printf("%.2f", currentNode->value);
    for(int i = 0; i < A->size-1; i++) {
        currentNode = currentNode->next;
        printf(", %.2f", currentNode->value);
    }
    printf("]\n");
    return 0;
}