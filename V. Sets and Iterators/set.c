#include "../IV. Dynamic Arrays and Linked Lists/dynamic_array.c"

typedef struct set {
    DynamicArray* A;
} Set;

Set* createSet() {
    Set* s = (Set*)malloc(sizeof(Set));
    s->A = createDynamicArray();
    return s;
}

//binary search
int is_member(Set* s, float x) {
    int a = 0;
    int b;
    for(b = (s->A->fill+1)/2; b >= 1; b /= 2) {
        while(get(s->A, a+b) <= x && a+b < (s->A->fill+1)) { a+=b; } 
    }
    if(get(s->A, a) - x < 0.0001) { return a; }
    return -1;
}

int add_member(Set* s, float x) {
    int a = is_member(s, x);
    if(get(s->A, a) < x) { insert(s->A, a+1, x); } 
    else if(get(s->A, a) > x) { insert(s->A, a, x); }
    return 0;
}

int remove_member(Set* s, float x) {
    int a = is_member(s, x);
    if(a > -1) { 
        return pop(s->A, a);
    }
    return 0;
}