#ifndef SORTING
#define SORTING


typedef unsigned int uint32;

void swap(void* a, void* b, uint32 size);
void bubble_sort_float(float* array, uint32 length);
void bubble_sort(void* array, uint32 typesize, uint32 length, float(*cmp_fn)(void* a, void* b));
void insertion_sort(void* array, uint32 typesize, uint32 length, float(*cmp_fn)(void* a, void* b));
void merge_sort(void* array, uint32 typesize, uint32 start, uint32 end, float(*cmp_fn)(void* a, void* b));
void quick_sort(void* array, uint32 typesize, uint32 start, uint32 end, float(*cmp_fn)(void* a, void* b));
void counting_sort(void* array, uint32 typesize, uint32 length, float(*cmp_fn)(void* a, void* b));
void bucket_sort(void* array, uint32 typesize, uint32 length, float(*cmp_fn)(void* a, void* b));
void bogosort(void* array, uint32 typesize, uint32 length, float(*cmp_fn)(void* a, void* b));

#endif