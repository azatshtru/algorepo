#include "headers/array_utils.h"
#include "headers/sorting.h"
#include "headers/binary_search.h"
#include "common_collections/include/vector.h"

float cmp_float(void* a, void* b) {
    return (*((float*)a)) - (*((float*)b));
}

int main() {
    float numbers[9];
    numbers[0] = -1.3;
    numbers[1] = 2.1;
    numbers[2] = 4.12;
    numbers[3] = 11.7;
    numbers[4] = 13.7;
    numbers[5] = 62.7;
    numbers[6] = 11.2;
    numbers[7] = 7.3;
    numbers[8] = 4.5;

    //quicksort(numbers, sizeof(float), 0, 8, cmp_float);
    array_print_primitive(numbers, 9, "%.2f");
    float v = -1.3;
    printf("%d\n", binary_search_local_maxima(numbers, sizeof(float), 9, cmp_float));

    return 0;
}