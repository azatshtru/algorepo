#include <stdlib.h>

struct fibonacci_heap_node {
    int key;
    unsigned int degree;
    char mark;

    struct fibonacci_heap_node* parent;
    struct fibonacci_heap_node* child;
    struct fibonacci_heap_node* left;
    struct fibonacci_heap_node* right;
};

typedef struct fibonacci_heap {
    unsigned int n;
    struct fibonacci_heap_node* min;
    struct fibonacci_heap_node* root_list;
} FibonacciHeap;
