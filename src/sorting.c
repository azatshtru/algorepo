#include <string.h>
#include "../headers/sorting.h"

void swap(void* a, void* b, uint32 size) {
    char temp[size];
    memcpy(temp, a, size);
    memcpy(a, b, size);
    memcpy(b, temp, size);
}

void bubble_sort_float(float* array, uint32 length) {
    int flag = 0;
    for(int i = 0; i < length-1; i++) {
        flag = 0;
        for(int j = 0; j < length-i-1; j++) {
            if(array[j] > array[j+1]) {
                swap(array+j, array+j+1, sizeof(float));
                flag = 1;
            }
        }
        if(flag == 0) {
            break;
        }
    }
}

void bubble_sort(void* array, uint32 typesize, uint32 length, float(*cmp_fn)(void* a, void* b)) {
    int flag = 0;
    for(int i = 0; i < (length-1); i++) {
        flag = 0;
        for(int j = 0; j < (length-i-1)*typesize; j += typesize) {
            if(cmp_fn(array+j, array+j+typesize) > 0) {
                swap(array+j, array+j+typesize, typesize);
                flag = 1;
            }
        }
        if(flag == 0) {
            break;
        }
    }
}