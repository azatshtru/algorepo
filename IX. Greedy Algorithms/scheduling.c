#include "../std/box.c"
#include "../std/vector.c"

typedef struct event {
    char* eventName;
    int start;
    int end;
} Event;

Event make_event(char* S, int i, int f) {
    Event e = { S, i, f };
    return e;
}

stdBox(Event)
stdVector(BoxEvent)

//A greedy strategy of choosing the shortest duration events does not work as larger events that do not overlap can exist.
//Simiarly, the strategy of choosing an event that begins as early as possible doesn't work cause it might take up the events that begin after and end early.
//Following, we can derive a greedy strategy of choosing the event that ends as soon as possible, so that other events have the time to begin.

int cmp_event_end(BoxEvent a, BoxEvent b) {
    return a.value->end<b.value->end?1:0;
}

int schedule(Vector(BoxEvent) events) {
    quick_sort(BoxEvent, events, 0, events->fill, cmp_event_end);
    int last = get(BoxEvent, events, 0).value->end;
    int count = 1;
    for(int i = 1; i < events->fill+1; i++) { 
        if(get(BoxEvent, events, i).value->start > last) {
            count++;
            last = get(BoxEvent, events, i).value->end;
        }
    }
    return count;
}

Vector(BoxEvent) generateExampleEvents() {
    Vector(BoxEvent) v = createVector(BoxEvent);
    push(BoxEvent, v, Box(Event, make_event("A", 800, 915)));
    push(BoxEvent, v, Box(Event, make_event("B", 845, 1000)));
    push(BoxEvent, v, Box(Event, make_event("C", 930, 1045)));
    push(BoxEvent, v, Box(Event, make_event("D", 1015, 1130)));
    push(BoxEvent, v, Box(Event, make_event("E", 1100, 1215)));
    push(BoxEvent, v, Box(Event, make_event("F", 1145, 1300)));
    push(BoxEvent, v, Box(Event, make_event("G", 1230, 1345)));
    push(BoxEvent, v, Box(Event, make_event("H", 1315, 1430)));
    push(BoxEvent, v, Box(Event, make_event("I", 1345, 1500)));
    push(BoxEvent, v, Box(Event, make_event("J", 1430, 1545)));
    push(BoxEvent, v, Box(Event, make_event("K", 1515, 1630)));
    push(BoxEvent, v, Box(Event, make_event("L", 1600, 1715)));
    return v;
}