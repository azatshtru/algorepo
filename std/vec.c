#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#ifndef VEC
#define VEC

typedef unsigned char uint8;
typedef signed char int8;
typedef char byte;

#define INIT_VEC_SIZE 8

typedef struct vec {
    uint8 cap;
    uint8 len;
    uint8 size;
    int8 alignment;
    byte array[];
} Vec;

byte* vec_new(uint8 size) {
    Vec* vec = (Vec*)malloc(sizeof(Vec)+(size*INIT_VEC_SIZE));
    vec->cap = INIT_VEC_SIZE;
    vec->len = 0;
    vec->size = size;
    vec->alignment = 0;
    return vec->array;
}

Vec* vec_address_from_array(void* array_ptr) { return (Vec*)((byte*)array_ptr-(uintptr_t)(&((Vec*)0)->array)); }

uint8 vec_len(void* array_ptr) { return vec_address_from_array(array_ptr)->len; }

Vec* vec_resize(Vec* v, uint8 new_len) {
    Vec* new_vec = (Vec*)malloc(sizeof(Vec)+(new_len*v->size));
    memcpy(new_vec->array, v->array, v->len*v->size);
    new_vec->cap = new_len;
    new_vec->len = v->len;
    new_vec->size = v->size;
    new_vec->alignment = 0;
    free(v);
    return new_vec;
}

void vec_free(void* array_ptr, void (*free_func)(void*)) {
    Vec* v = vec_address_from_array(array_ptr);
    if(free_func != NULL) {
        for(int i = 0; i < v->len*v->size; i+=v->size) { free_func(array_ptr+i); }
    }
    free(v);
}

//void vec_push(void* array_ptr, byte* value) {
    //Vec* v = vec_address_from_array((byte*)array_ptr);
    //if(v->len==v->cap) { array_ptr = (void*)vec_resize(v, v->cap*2)->array; }
    //memcpy(array_ptr+vec_address_from_array(array_ptr)->len++, value, vec_address_from_array(array_ptr)->size);
//}

#define __vec_new__(type) (type*)vec_new(sizeof(type))

#define __vec_push__(array_ptr, value) ({\
Vec* v = vec_address_from_array((byte*)array_ptr);\
if(v->len==v->cap) { array_ptr = (void*)vec_resize(v, v->cap*2)->array; }\
array_ptr[vec_address_from_array(array_ptr)->len++] = value;\
})

#define __vec_pop__(type, array_ptr, popidx) ({\
Vec* v = vec_address_from_array(array_ptr);\
uint8 index = popidx<0?v->len+popidx:popidx;\
type value = array_ptr[index];\
for(int i = index; i < v->len-1; i++) { array_ptr[i] = array_ptr[i+1]; }\
--v->len;\
if(v->cap >= INIT_VEC_SIZE*2 && v->len == v->cap/2) { array_ptr = (void*)vec_resize(v, v->cap/2)->array; }\
value;\
})

#define __vec_print_primitive__(array_ptr, type_specifier) ({\
printf("vec![ ");\
for(int i = 0; i < vec_address_from_array(array_ptr)->len; i++) { printf(type_specifier, array_ptr[i]); printf(", "); }\
printf("\b\b ]\n");})

#define __vec_print__(array_ptr, print_func) ({\
printf("vec![ ");\
for(int i = 0; i < vec_address_from_array(array_ptr)->len; i++) { print_func(array_ptr[i]); printf(", "); }\
printf("\b\b ]\n");})

uint8 vec_quicksort_partition(void* array_ptr, int8 lo, int8 hi, int8 (*cmp_func)(void*, void*)) {
    uint8 size = vec_address_from_array(array_ptr)->size;
    uint8 pivot = hi*size;
    int8 index = (lo-1)*size;
    for(uint8 i = lo*size; i < hi*size; i+=size) {
        if(cmp_func(array_ptr+i, array_ptr+pivot) < 0) {
            index+=size;
            byte temp_value[size];
            memcpy(temp_value, array_ptr+i, size);
            memcpy(array_ptr+i, array_ptr+index, size);
            memcpy(array_ptr+index, temp_value, size);
        }
    }
    index+=size;
    byte temp_value[size];
    memcpy(temp_value, array_ptr+pivot, size);
    memcpy(array_ptr+pivot, array_ptr+index, size);
    memcpy(array_ptr+index, temp_value, size);
    return index/size;
}

void vec_quicksort(void* array_ptr, int8 lo, int8 hi, int8 (*cmp_func)(void*, void*)) {
    if(lo >= hi || lo < 0) { return; }
    uint8 index = vec_quicksort_partition(array_ptr, lo, hi, cmp_func);
    vec_quicksort(array_ptr, lo, index-1, cmp_func);
    vec_quicksort(array_ptr, index+1, hi, cmp_func);
}

#endif