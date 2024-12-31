#include <stdio.h>
#include "headers/fibonacci_heap.h"

int main() {
    FibonacciHeap heap = fibonacci_heap_new();
    for(int i = 0; i < 25; i++) {
        fibonacci_heap_insert_node(&heap, i);
    }
    for(int i = 0; i < 2; i++) {
        struct fibonacci_heap_node* node = fibonacci_heap_extract_min(&heap);
        free(node);
    }
    fibonacci_heap_traverse(heap.root_list, 0);
    return 0;
}
