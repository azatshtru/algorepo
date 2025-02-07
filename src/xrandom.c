#include <stdlib.h>
#include <time.h>
#include "../headers/xrandom.h"

void random_init_seed() {
    static int is_set = 0;
    if(!is_set) {
        srand(time(0));
        is_set = 1;
    }
    rand();
}

float randf_01() {
    random_init_seed();
    return (float)rand()/RAND_MAX;
}

int randi_range(int a, int b) {
    random_init_seed();
    return a + randf_01() * (b-a);
}
