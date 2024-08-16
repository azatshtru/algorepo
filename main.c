#include "headers/array_utils.h"
#include "common_collections/include/vector.h"

int main() {
    vector(int) v = vec_new(int);

    vec_push(v, 6);
    vec_push(v, 8);
    vec_push(v, -8);
    vec_print_primitive(v, "%d");

    float numbers[5];
    array_random_01(numbers, 5);

    array_print_primitive(numbers, 5, "%.2f");
    printf("%.2f, %.2f, %.2f", array_sum_float(numbers, 5), array_min_float(numbers, 5), array_max_float(numbers, 5));

    return 0;
}