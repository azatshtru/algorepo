#include <stdio.h>
#include "headers/array_utils.h"

int main() {
    int array[8] = { 1, 3, 2, 5, 1, 1, 2, 3 };
    int start;
    int end;

    array_print_primitive(array, 8, "%d");

    subarray_with_sum(array, 8, 8, &start, &end);

    printf("start: %d\n", start);
    printf("end: %d\n", end);

    return 0;
}
