#include <stdlib.h>

typedef struct event {
    char* eventName;
    int start;
    int end;
} Event;

Event* createEventList(int n) {
    Event* eventList = (Event*)malloc(n*sizeof(Event));
    return eventList;
}

int setEvent(Event* eventList, int i, char* S, int start, int end) {
    Event e; 
    e.eventName = S;
    e.start = start;
    e.end = end;
    *(eventList+i) =  e;

    return 0;
}

