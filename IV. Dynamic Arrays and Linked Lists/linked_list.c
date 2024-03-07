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

LinkedList* Linked_List() {
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

int pop(LinkedList* A, int i) {
    Node* temp;
    if(i==0){
        temp = A->head;
        A->head = A->head->next;
    } else if(i==A->size-1) {
        temp = A->tail;
    } else {
        Node* ni = A->head;
        for(int j = 0; j < i-1; j++) { ni = ni->next; }
        temp = ni->next;
        ni->next = ni->next->next;
    }
    float v = temp->value;
    free(temp);
    A->size -= 1;
    return v;
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