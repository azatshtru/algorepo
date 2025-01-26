#include "../headers/sorting.h"

struct event {
    char* name;
    int start;
    int end;
};

float event_cmp_by_end(void* x, void* y) {
    struct event a = *((struct event*)x);
    struct event b = *((struct event*)y);
    return a.end - b.end;
}

int event_schedule(struct event* events, int len) {
    quicksort(events, sizeof(struct event), 0, len - 1, event_cmp_by_end);

    int last = events[len - 1].end;
    int count = 1;
    for(int i = 1; i < len; i++) { 
        if(events[i].start > last) {
            ++count;
            last = events[i].end;
        }
    }
    return count;
}
