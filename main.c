#include "headers/array_utils.h"
#include "headers/sorting.h"
#include "common_collections/include/vector.h"

float cmp_float(void* a, void* b) {
    return *((float*)a) - *((float*)b);
}

int main() {
    float numbers[12];
    array_random_01(numbers, 12);
    array_print_primitive(numbers, 12, "%.2f");
    bubble_sort(numbers, sizeof(float), 12, cmp_float);
    array_print_primitive(numbers, 12, "%.2f");


    return 0;
}