#include "../headers/fibonacci_heap.h"

struct fibonacci_heap_node* fibonacci_heap_node_new(int key) {
    struct fibonacci_heap_node* node_ptr = malloc(sizeof(struct fibonacci_heap_node));
    struct fibonacci_heap_node node = { key, 0, 0, NULL, NULL, NULL, NULL };
    *node_ptr = node;
    return node_ptr;
}

FibonacciHeap fibonacci_heap_new() {
    FibonacciHeap heap = { 0, NULL, NULL };
    return heap;
}

struct fibonacci_heap_node* fibonacci_heap_min(FibonacciHeap* heap) {
    return heap->min;
}

void fibonacci_heap_merge_with_root_list(FibonacciHeap* heap, struct fibonacci_heap_node* node) {
    if(heap->root_list == NULL) {
        heap->root_list = node;
    } else {
        node->right = heap->root_list;
        node->left = heap->root_list->left;
        heap->root_list->left->right = node;
        heap->root_list->left = node;
    }
}

struct fibonacci_heap_node* fibonacci_heap_insert_node(FibonacciHeap* heap, int key) {
    struct fibonacci_heap_node* node = fibonacci_heap_node_new(key);
    node->left = node;
    node->right = node;

    fibonacci_heap_merge_with_root_list(heap, node);
    if(heap->min == NULL || node->key < heap->min->key) {
        heap->min = node;
    }
    ++heap->n;
    return node;
}

FibonacciHeap fibonacci_heap_union(FibonacciHeap* f1, FibonacciHeap* f2) {
    FibonacciHeap heap = fibonacci_heap_new();
    heap.root_list = f1->root_list;

    heap.min = f1->min < f2->min ? f1->min : f2->min;

    struct fibonacci_heap_node* last = f2->root_list->left;
    f2->root_list->left = heap.root_list->left;
    heap.root_list->left->right = f2->root_list;
    heap.root_list->left = last;
    heap.root_list->left->right = heap.root_list;

    heap.n = f1->n + f2->n;
    return heap;
}

void fibonacci_heap_remove_from_root_list(FibonacciHeap* heap, struct fibonacci_heap_node* node) {
    if(node == heap->root_list) {
        heap->root_list = node->right;
    }
    node->left->right = node->right;
    node->right->left = node->left;
}

void fibonacci_heap_consolidate(FibonacciHeap* heap) {
        
}

struct fibonacci_heap_node* fibonacci_heap_extract_min(FibonacciHeap* heap) {
    struct fibonacci_heap_node* z = heap->min;
    if(z != NULL) {
        if(z->child != NULL) {
            struct fibonacci_heap_node* child = z->child;
            for(int i = 0; i < z->degree; i++) {
                struct fibonacci_heap_node* next_sibling = child->right;
                fibonacci_heap_merge_with_root_list(heap, child);
                child->parent = NULL;
                child = next_sibling;
            }
        }
        fibonacci_heap_remove_from_root_list(heap, z);

        if(z == z->right) {
            heap->min = NULL;
            heap->root_list = NULL;
        } else {
            heap->min = z->right;
            fibonacci_heap_consolidate(heap);
        }
        --heap->n;
    }
    return z;
}
