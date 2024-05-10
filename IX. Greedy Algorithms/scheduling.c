#include "../std/vec.c"

//A greedy strategy of choosing the shortest duration events does not work as larger events that do not overlap can exist.
//Simiarly, the strategy of choosing an event that begins as early as possible doesn't work cause it might take up the events that begin after and end early.
//Following, we can derive a greedy strategy of choosing the event that ends as soon as possible, so that more events can begin.

typedef struct event {
    char* event_name;
    int start;
    int end;
} Event;

Event event_new(char* event_name, int start, int end) {
    Event e = { event_name, start, end };
    return e;
}

void event_print(Event event) { printf("event!{ %s: %d - %d }", event.event_name, event.start, event.end); }

int8 event_cmp_end(void* x, void* y) {
    Event a = *(Event*)x;
    Event b = *(Event*)y;
    return a.end<b.end?-1:0;
}

uint8 event_schedule(Event* events) {
    vec_quicksort(events, 0, vec_len(events)-1, event_cmp_end);
    uint8 last = events[vec_len(events)-1].end;
    uint8 count = 1;
    for(int i = 1; i < vec_len(events); i++) { 
        if(events[i].start > last) {
            ++count;
            last = events[i].end;
        }
    }
    return count;
}

Event* event_samples() {
    Event* events = __vec_new__(Event);
    __vec_push__(events, event_new("A", 800, 915));
    __vec_push__(events, event_new("B", 845, 1000));
    __vec_push__(events, event_new("C", 930, 1045));
    __vec_push__(events, event_new("D", 1015, 1130));
    __vec_push__(events, event_new("E", 1100, 1215));
    __vec_push__(events, event_new("F", 1145, 1300));
    __vec_push__(events, event_new("G", 1230, 1345));
    __vec_push__(events, event_new("H", 1315, 1430));
    __vec_push__(events, event_new("I", 1345, 1500));
    __vec_push__(events, event_new("J", 1430, 1545));
    __vec_push__(events, event_new("K", 1515, 1630));
    __vec_push__(events, event_new("L", 1600, 1715));
    return events;
}