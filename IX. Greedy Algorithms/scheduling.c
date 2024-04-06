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
stdVector(int)

Vector(BoxEvent) generateExampleEventList() {
    Vector(BoxEvent) v = createVector(BoxEvent);
    push(BoxEvent, v, Box(Event, make_event("A", 1, 3)));
    push(BoxEvent, v, Box(Event, make_event("B", 2, 5)));
    push(BoxEvent, v, Box(Event, make_event("C", 3, 9)));
    push(BoxEvent, v, Box(Event, make_event("D", 6, 8)));
    return v;
}

int sortEventsByEnd(Vector(BoxEvent) events) {
    
}

//A greedy strategy of choosing the shortest duration events does not work as larger events that do not overlap can exist.
//Simiarly, the strategy of choosing an event that begins as early as possible doesn't work cause it might take up the events that begin after and end early.
//Following, we can derive a greedy strategy of choosing the event that ends as soon as possible, so that other events have the time to begin.
int schedule(Vector(BoxEvent) eventList) {
    int a = 0;
    int b = 0;
    for(int i = 0; i < eventList->fill+1; i++) {
        int cancel = get(BoxEvent, eventList, i).value->end;
    }
}