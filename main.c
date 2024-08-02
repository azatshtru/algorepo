#include "headers/array_utils.h"

int main() {
    printf("Hello, world!\n");
    float a[8];
    array_random_01(a, 8);
    array_print_primitive(a, 8, "%.2f");
    array_random_01(a, 8);
    array_print_primitive(a, 8, "%.2f");
}