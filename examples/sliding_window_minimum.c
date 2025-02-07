#include "../headers/queue.h"

/// sliding windows can be used to track properties in local subarrays
int sliding_window_minimum(int* array, int len, int windowsize, int* out) {
    VecDeque(int) q = queue_new(int);
    int j = 0;
    for(int i = 0; i < windowsize; i++) {
        while(!queue_is_empty(q) && array[queue_back(q)] > array[i]) {
            queue_pop_back(q);
        }
        queue_push_back(q, i);
    }
    for(int i = windowsize; i < len; i++) {
        out[j++] = array[queue_front(q)];
        if(!queue_is_empty(q) && queue_front(q) <= i - windowsize) {
            queue_pop_front(q);
        }
        while(!queue_is_empty(q) && array[queue_back(q)] >= array[i]) {
            queue_pop_back(q);
        }
        queue_push_back(q, i);
    }
    out[j] = array[queue_front(q)];

    queue_free(q, NULL);
    return 0;
}

int main() {
    return 0;
}
