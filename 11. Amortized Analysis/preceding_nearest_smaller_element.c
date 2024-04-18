#include <stdlib.h>

typedef struct stack {
    int length;
    int fill;
    int* A;
} Stack;

Stack* init_stack(int length) {
    Stack* s = (Stack*)malloc(sizeof(Stack));
    s->length = length;
    s->fill = 0;
    s->A = (int*)malloc(sizeof(int)*length);
    return s;
}

int push_stack(Stack* s, int x) {
    if(s->fill>=s->length) { printf("Nothing happened due to stack overflow."); return -1; }
    s->A[s->fill++] = x;
    return 0;
}

int pop_stack(Stack* s) {
    if(s->fill<=0) { printf("Nothing happened because stack empty."); return -1; }
    int k = s->A[s->fill--];
    return k;
}

int peek_stack_top(Stack* s) {
    return s->A[s->fill-1];
}

int free_stack(Stack* s) {
    free(s->A);
    free(s);
    return 0;
}

//For each element, find the nearest smaller element that precedes it.
int nearest_preceding_smaller_element(int len, int* A) {
    Stack* s = init_stack(len);
    int P[len];
    P[0] = -1;
    push_stack(s, A[0]);

    for(int i = 1; i < len; i++) { 
        if(A[i]>peek_stack_top(s)){
            push_stack(s, A[i]);
        } else {
            while(A[i]<=peek_stack_top(s) && s->fill>0) { pop_stack(s); }
            push_stack(s, A[i]);
        }
        printf("\n");
        for(int i = 0; i < len; i++) { printf("%d ", s->A[i]); }
        printf("\n");
        P[i] = s->fill<=1 ? -1 : s->A[s->fill-2];
    }
    printf("\n");
    for(int i = 0; i < len; i++) { printf("%d ", P[i]); }
    printf("\n");

    free_stack(s);
    return 0;
}