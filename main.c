#include "headers/array_utils.h"
#include "headers/sorting.h"
#include "common_collections/include/vector.h"

float cmp_float(void* a, void* b) {
    return (*((float*)a)) < (*((float*)b)) ? -1 : 1;
}

int main() {
    float numbers[12];
    array_random_01(numbers, 12);
    array_print_primitive(numbers, 12, "%.2f");
    merge_sort(numbers, sizeof(float), 0, 11, cmp_float);
    array_print_primitive(numbers, 12, "%.2f");

    return 0;
}