#include <string.h>
#include "../headers/sorting.h"
#include "../headers/array_utils.h"

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

void merge_sort(void* array, uint32 typesize, uint32 start, uint32 end, float(*cmp_fn)(void* a, void* b)) {
    if(end<=start) {
        return;
    }
    uint32 mid = (end+start)/2;
    merge_sort(array, typesize, start, mid, cmp_fn);
    merge_sort(array, typesize, mid+1, end, cmp_fn);

    uint32 n = (end-start+1)*typesize;
    char temp_merged[n];
    uint32 a = start*typesize;
    uint32 b = (mid+1)*typesize;
    uint32 i = 0;
    while(a <= mid*typesize && b <= end*typesize) {
        if(cmp_fn(array+a, array+b) < 0) {
            memcpy(temp_merged+i, array+a, typesize);
            a += typesize;
        } else {
            memcpy(temp_merged+i, array+b, typesize);
            b += typesize;
        }
        i += typesize;
    }
    uint32 remaining_stuff = a > mid*typesize ? b : a;
    memcpy(temp_merged+i, array+remaining_stuff, n - i);
    memcpy(array+(start*typesize), temp_merged, n);
}

