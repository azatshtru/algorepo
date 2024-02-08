#include <stdio.h>
#include "../../I. Arrays, Traversal and Flags/array_traversal_examples.c"

#define RED   "\x1B[31m"
#define GRN   "\x1B[32m"
#define YEL   "\x1B[33m"
#define BLU   "\x1B[34m"
#define MAG   "\x1B[35m"
#define CYN   "\x1B[36m"
#define WHT   "\x1B[37m"
#define RESET "\x1B[0m"

int assert_eq(char* test_name, float a, float b) {

    printf(CYN "\n------------------------\n\n" RESET);
    printf(CYN "Performing test " RESET);
    printf(YEL "%s\n" RESET, test_name);
    if(a == b) {
        printf(GRN "TEST PASSED\n" RESET);

    } else {
        printf(RED "TEST FAILED: " RESET);
        printf("expected %f, found %f\n", b, a);
    }
    printf(CYN "\n------------------------\n" RESET);
    return 0;
}

int basic_tests() {
    float* A1 = Array(5);
    prettyPrint(A1);

    set(A1, 2, -1.4);
    assert_eq("array value setting and indexing", get(A1, 2), -1.4);

    set(A1, 4, -1.4);
    set(A1, 0, 0.011);
    set(A1, 1, 0.7);
    set(A1, 3, 1.56);
    prettyPrint(A1);
    assert_eq("finding array length", len(A1), 5);

    printf("All the values in the array between zero and one\n");
    nums_bw01(A1);

    assert_eq("number of -1.4s in the array", count(A1, -1.4), 2);
    assert_eq("number of 1.56s in the array", count(A1, 1.56), 1);

    clear(A1);
    return 0;
}

int main () {
    basic_tests();
    return 0;
}