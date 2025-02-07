#ifndef ARRAY_UTILS
#define ARRAY_UTILS

#include <string.h>
#include <stdio.h>

typedef unsigned int uint32;

#define array_set_zeroes(array_ptr, length) do {            \
    memset((array_ptr), 0, sizeof((array_ptr)[0])*(length));\
} while(0)

#define array_print(array_ptr, length, print_fn) do {       \
    printf("[");                                            \
    for(uint32 i = 0; i < (length); i++) {                  \
        print_fn((array_ptr)[i]);                           \
        printf(", ");                                       \
    }                                                       \
    printf("\b\b]\n");                                      \
} while(0)

#define array_print_primitive(array_ptr, length, type_specifier) do {   \
    printf("[");                                                        \
    for(uint32 i = 0; i < (length); i++) {                              \
        printf((type_specifier), (array_ptr)[i]);                       \
        printf(", ");                                                   \
    }                                                                   \
    printf("\b\b]\n");                                                  \
} while(0)

void array_random_01(float* array_ptr, uint32 length);
float array_sum_float(float* array_ptr, uint32 length);
float array_min_float(float* array_ptr, uint32 length);
float array_max_float(float* array_ptr, uint32 length);

int subarray_with_sum(int* array, int len, int target, int* start, int* end);

#endif
