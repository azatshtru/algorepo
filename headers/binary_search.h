#ifndef BINARY_SEARCH
#define BINARY_SEARCH

int binary_search_r(void* array, int typesize, int length, void* value, float(*cmp_fn)(void*, void*));
int binary_search_l(void* array, int typesize, int length, void* value, float(*cmp_fn)(void*, void*));
int binary_search_local_maxima(void* array, int typesize, int length, float(*cmp_fn)(void*, void*));


#endif