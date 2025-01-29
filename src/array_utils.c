#include <stdlib.h>
#include <time.h>
#include "../headers/xrandom.h"
#include "../headers/array_utils.h"

// Array on stack using []
// Array on heap using malloc

void array_random_01(float* array_ptr, uint32 length) {
    random_init_seed();
    rand();
    for(uint32 i = 0; i < length; i++) {
        array_ptr[i] = (float)rand()/RAND_MAX;
    }
}

// Traversal is technique used to pass through each element of an array to analyse it.
// Additionally, a flag can be used to keep track of properties of the entire array that are
// derived through individual analysis of elements.

float array_sum_float(float* array_ptr, uint32 length) {
    float sum = 0; // initializing the flag
    for(uint32 i = 0; i < length; i++) { // traversal
        sum += array_ptr[i]; // updating the flag
    }
    return sum;
}

float array_min_float(float* array_ptr, uint32 length) {
    float min = array_ptr[0];
    for(uint32 i = 1; i < length; i++) {
        min = array_ptr[i] < min ? array_ptr[i] : min;
    }
    return min;
}

float array_max_float(float* array_ptr, uint32 length) {
    float max = array_ptr[0];
    for(uint32 i = 1; i < length; i++) {
        max = array_ptr[i] > max ? array_ptr[i] : max;
    }
    return max;
}

/// from an array of numbers, find a continuous subarray whose values sum to the given target
int subarray_with_sum(int* array, int len, int target, int* start, int* end) {
    int i = 0;
    int j = 0;
    int sum = array[i];
    while(i < len || j < len) {
        while(sum < target) {
            sum += array[j++];
        }
        if(sum == target) {
            *start = i;
            *end = j;
            return 1;
        }
        while(sum > target) {
            sum -= array[i++];
        }
    }
    return 0;
}
