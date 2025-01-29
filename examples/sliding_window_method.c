#include "../headers/queue.h"

/// sliding windows can be used to track properties in local subarrays

int sliding_window_minimum(int* array, int len, int windowsize, int* minima) {
    VecDeque(int) q = queue_new(int);
    int j = 0;
    for(int i = 0; i < windowsize; i++) {
        while(!queue_is_empty(q) && array[queue_back(q)] > array[i]) {
            queue_pop_back(q);
        }
        queue_push_back(q, i);
    }
    for(int i = windowsize; i < len; i++) {
        minima[j++] = array[queue_front(q)];
        if(!queue_is_empty(q) && queue_front(q) <= i - windowsize) {
            queue_pop_front(q);
        }
        while(!queue_is_empty(q) && array[queue_back(q)] >= array[i]) {
            queue_pop_back(q);
        }
        queue_push_back(q, i);
    }
    minima[j] = array[queue_front(q)];
    return 0;
}

int main() {
    int array[8] = { 1, 3, -1, -3, 5, 3, 6, 7 };
    int sliding_window_minima[6];
    sliding_window_minimum(array, 8, 3, sliding_window_minima);
    for(int i = 0; i < 6; i++) {
        printf("%d, ", sliding_window_minima[i]);
    }
    printf("\n");
    return 0;
}
