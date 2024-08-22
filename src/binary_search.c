#include "../headers/binary_search.h"
#include <stdio.h>

int close_to_zero(float epsilon) {
    if(epsilon < 0.000001 && epsilon > -0.000001) {
        return 1;
    }
    return 0;
}

int binary_search_r(void* array, int typesize, int length, void* value, float(*cmp_fn)(void*, void*)) {
    int a = 0;
    for(int b = length/2; b >= 1; b /= 2) {
        while((cmp_fn(array+((a+b)*typesize), value) <= 0
            || close_to_zero(cmp_fn(array+((a+b)*typesize), value)))
            && a+b < length)
        { a += b; }
    }
    return a;
}

int binary_search_l(void* array, int typesize, int length, void* value, float(*cmp_fn)(void*, void*)) {
    int b = length - 1;
    for(int a = length/2; a >= 1; a /= 2) {
        while((cmp_fn(array+((b-a)*typesize), value) >= 0
            || close_to_zero(cmp_fn(array+((b-a)*typesize), value)))
            && b-a >= 0)
        { b -= a; }
    }
    return b;
}

// Binary search can be used to calculate local maxima of some array (if array has only one maxima).
int binary_search_local_maxima(void* array, int typesize, int length, float(*cmp_fn)(void*, void*)) {
    int a = -1;
    for(int b = length/2; b >= 1; b /= 2) {
        while(cmp_fn(array+((a+b)*typesize), array+((a+b+1)*typesize)) < 0 && a+b < length) {
            a += b;
        }
    }
    return a+1;
}