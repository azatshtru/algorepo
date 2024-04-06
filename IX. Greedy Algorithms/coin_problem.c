#include "../V. Sets and Iterators/set.c"

//This is the greedy solution of coin problem, this works with Euro coins.
//However this won't work with any set of coins and a dynamic programming approach would be required.

int minimum_coins(Set* c, int k) {
    int count = 0;
    int x = k;
    int i = c->A->fill;
    while(x > 0) {
        while(x < get(c->A, i)) { i--; }
        x -= get(c->A, i);
        count++;
    }
    return count;
}

Set* generateEuroCoins() {
    Set* c = createSet();
    add_member(c, 1);
    add_member(c, 2);
    add_member(c, 5);
    add_member(c, 10);
    add_member(c, 20);
    add_member(c, 50);
    add_member(c, 100);
    return c;
}