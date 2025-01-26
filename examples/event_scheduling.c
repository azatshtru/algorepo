#include "../headers/sorting.h"

// a greedy strategy of choosing the shortest duration events does not work
// as larger events that do not overlap can exist.
// the strategy of choosing an event that begins as early as possible doesn't work
// because it might take up the events that begin after and end early.
// following, we can derive a greedy strategy of choosing the event that ends as soon as possible,
// so that more events can begin as soon as possible.

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

int event_scheduling(struct event* events, int len) {
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

int main() {
    return 0;
}
