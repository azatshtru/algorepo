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

Vec* vec_address_from_array(void* array_ptr) { return array_ptr-(uintptr_t)(&((Vec*)0)->array); }

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

byte* vec_pop(byte** array_ptr, uint8 index) {
    Vec* v = vec_address_from_array(*array_ptr);
    memcpy(*array_ptr+(index*v->size), *array_ptr+((index+1)*v->size), v->size*(v->len-index));
    --v->len;
    if(v->cap >= INIT_VEC_SIZE*2 && v->len==v->cap/2) { *array_ptr = (void*)vec_resize(v, v->cap/2)->array; }
    return NULL;
}

void vec_free(void* array_ptr) { free(vec_address_from_array(array_ptr)); }

#define __vec_new__(type) (type*)vec_new(sizeof(type));

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

#define __vec_print__(array_ptr, print_func_ptr) ({\
printf("vec![ ");\
for(int i = 0; i < vec_address_from_array(array_ptr)->len; i++) { print_func_ptr(array_ptr[i]); printf(", "); }\
printf("\b\b ]\n");})

#endif