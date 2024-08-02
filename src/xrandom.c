#include <stdlib.h>
#include <time.h>
#include "../headers/xrandom.h"

void random_init_seed() {
    static int is_set = 0;
    if(!is_set) {
        srand(time(0));
        is_set = 1;
    }
}