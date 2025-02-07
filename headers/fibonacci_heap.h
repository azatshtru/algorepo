#include <stdio.h>
#include <stdlib.h>
#include "miniqutils.h"

#ifndef FIBONACCI_HEAP
#define FIBONACCI_HEAP

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

struct fibonacci_heap_node* fibonacci_heap_node_new(int key);
FibonacciHeap fibonacci_heap_new();
struct fibonacci_heap_node* fibonacci_heap_min(FibonacciHeap* heap);
void fibonacci_heap_merge_with_root_list(FibonacciHeap* heap, struct fibonacci_heap_node* node);
struct fibonacci_heap_node* fibonacci_heap_insert_node(FibonacciHeap* heap, int key);
FibonacciHeap fibonacci_heap_union(FibonacciHeap* f1, FibonacciHeap* f2);
void fibonacci_heap_remove_from_root_list(FibonacciHeap* heap, struct fibonacci_heap_node* node);
void fibonacci_heap_merge_root_node_with_child_list(
    FibonacciHeap* heap,
    struct fibonacci_heap_node* x,
    struct fibonacci_heap_node* y
);
unsigned int fibonacci_heap_root_list_length(FibonacciHeap* heap);
void fibonacci_heap_cdll_to_array(
    struct fibonacci_heap_node* head, 
    struct fibonacci_heap_node** array,
    unsigned int length
);
void fibonacci_heap_consolidate(FibonacciHeap* heap);
struct fibonacci_heap_node* fibonacci_heap_extract_min(FibonacciHeap* heap);

void fibonacci_heap_decrease_key(FibonacciHeap* heap, struct fibonacci_heap_node* node, int key);

void fibonacci_heap_cut(FibonacciHeap* heap, struct fibonacci_heap_node* node, struct fibonacci_heap_node* parent);
void fibonacci_heap_cascading_cut(FibonacciHeap* heap, struct fibonacci_heap_node* node);
void fibonacci_heap_remove_from_child_list(
    FibonacciHeap* heap,
    struct fibonacci_heap_node* parent,
    struct fibonacci_heap_node* node
);
struct fibonacci_heap_node* fibonacci_heap_delete(FibonacciHeap* heap, struct fibonacci_heap_node* node);
void fibonacci_heap_traverse_and_print_keys(struct fibonacci_heap_node* node, int depth);

#endif
