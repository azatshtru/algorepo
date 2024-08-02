#include <stdlib.h>
#include <time.h>
#include "../headers/xrandom.h"
#include "../headers/array_utils.h"

// Traversal is technique used to pass through each element of an array to analyse it.
// Additionally, a flag can be used to keep track of properties of the entire array that are derived through individual analysis of elements.

void array_random_01(float* array_ptr, uint32 length) {
    random_init_seed();
    rand();
    for(uint32 i = 0; i < length; i++) {
        array_ptr[i] = (float)rand()/RAND_MAX;
    }
}