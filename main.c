#include "headers/array_utils.h"

int main() {
    printf("Hello, world!\n");
    char a[8];
    array_set_zeroes(a, 8);
    array_print_primitive(a, 8, "%d");
    a[4] = 3;
    a[1] = 2;
    a[2] = -2;
    array_print_primitive(a, 8, "%d");
}