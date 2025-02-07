#include "../headers/queue.h"

/// stacks can be used to keep track of subjects of interest while traversing through an array in amortized O(n) time

#define stack_new queue_new
#define stack_free queue_free
#define stack_push queue_push_back
#define stack_pop queue_pop_back
#define stack_top queue_back
#define stack_is_empty queue_is_empty
#define Stack VecDeque

/// for each element, find the nearest smaller element that precedes it
int nearest_preceding_smaller_values(int* array, int len, int* nearest_smaller) {
    Stack(int) s = stack_new(int);

    for(int i = 0; i < len; i++) {
        while(!stack_is_empty(s) && stack_top(s) >= array[i]) {
            stack_pop(s);
        }
        if(stack_is_empty(s)) {
            nearest_smaller[i] = array[i];
        } else {
            nearest_smaller[i] = stack_top(s);
        }
        stack_push(s, array[i]);
    }
    stack_free(s, NULL);
    return 0;
}

int main() {
    return 0;
}
