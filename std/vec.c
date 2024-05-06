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
    int8 len;
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

Vec* vec_address_from_array(void* array_ptr) { return array_ptr-(uintptr_t)(&((Vec*)0)->array); }

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

void vec_free(byte* array_ptr) { free(vec_address_from_array(array_ptr)); }

#define __vec_new__(type) (type*)vec_new(sizeof(type));

#define __vec_push__(array_ptr, value) {\
Vec* v = vec_address_from_array((byte*)array_ptr);\
if(v->len==v->cap) { array_ptr = (void*)vec_resize(v, v->cap*2)->array; }\
array_ptr[vec_address_from_array(array_ptr)->len++] = value;\
}

#define __vec_print__(array_ptr)\
printf("\n[ ");\
for(int i = 0; i < vec_address_from_array(array_ptr)->len; i++) { printf("%d, ", array_ptr[i]); }\
printf("\b\b ]\n");

#define __vec_free__(array_ptr) vec_free((byte*)array_ptr);

#endif