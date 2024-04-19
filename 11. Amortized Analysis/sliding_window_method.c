#include "../VI. Queues/deque.c"

//sliding windows can be used to track properties in local subarrays.
//As an example here is the algorithm to calculate the sliding window minimum.
//k represents the window size.

int sliding_window_minimum(int length, int* A, int k) {
    Deque* q = createDeque();
    int p = 0;
    for(int i = 0; i < length; i++) {
        displayDeque(q);
        if(i>=k) {
            ++p;
            if(q->size>0) { 
                int j = (int)pop_back(q);
                if(j > p-1) { push_back(q, j); }
            }
        }
        int v;
        if(q->size>0) { v = (int)pop_front(q); push_front(q, v); }
        if(q->size==0 || A[v] < A[i]) { push_front(q, i); continue; }
        while(q->size > 0 && A[v] > A[i]) { v = (int)pop_front(q); }
        if(A[v] < A[i]) { push_front(q, v); }
        push_front(q, i);
    }
    displayDeque(q);
    return 0;
}