#include <stdio.h>
#include "../../II. Sorting/sorting.c"

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
    if(a - b < 0.0001 || b - a < 0.0001) {
        printf(GRN "TEST PASSED\n" RESET);

    } else {
        printf(RED "TEST FAILED: " RESET);
        printf("expected %f, found %f\n", b, a);
    }
    printf(CYN "\n------------------------\n" RESET);
    return 0;
}

float* get_random_array(int n, int a, int b, int seed) {
    float* A = Array(n);
    srand(seed);
    for(int i = 0; i < n; i++) {
        float r = a + ((float)rand()/RAND_MAX * (b - a));
        set(A, i, r);
    }
    return A;
}

int basic_tests() {
    printf("\n--------------------\nBASIC ARRAY TESTING\n-----------------------\n");
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

    assert_eq("sum of array", sum(A1), -0.529000);

    assert_eq("number of -1.4s in the array", count(A1, -1.4), 2);
    assert_eq("number of 1.56s in the array", count(A1, 1.56), 1);

    clear(A1);
    printf("\n\n");
    return 0;
}

int sorting_tests() {
    printf("\n---------------------\nSORTING TESTS\n--------------------\n");
    float* A1 = Array(10);
    set(A1, 0, 1.57);
    set(A1, 1, 1.9);
    set(A1, 2, 0.52);
    set(A1, 3, -4.71);
    set(A1, 4, 2.11);
    set(A1, 5, -23.67);
    set(A1, 6, -2.7);
    set(A1, 7, 4.77);
    set(A1, 8, 20);
    set(A1, 9, -101.5);
    prettyPrint(A1);

    bubble_sort(A1);
    prettyPrint(A1);
    
    shuffle(A1);
    prettyPrint(A1);

    merge_sort(A1, 0, len(A1));
    prettyPrint(A1);

    clear(A1);
    printf("\n\n");
    return 0;
}

int counting_sort_test() {
    printf("\n---------------------\nCOUNTING SORT TEST\n--------------------\n");
    float* A1 = Array(10);
    set(A1, 0, 101);
    set(A1, 1, 11);
    set(A1, 2, 101);
    set(A1, 3, 71);
    set(A1, 4, 11);
    set(A1, 5, 67);
    set(A1, 6, 27);
    set(A1, 7, 77);
    set(A1, 8, 20);
    set(A1, 9, 101);
    prettyPrint(A1);

    counting_sort(A1);
    prettyPrint(A1);

    printf("\n\n");
    clear(A1);
    return 0;
}

int bogosort_test() {
    printf("\n---------------------\nBOGOSORT >:)\n--------------------\n");
    float* A1 = get_random_array(4, -2, 5, 2);
    prettyPrint(A1);

    bogosort(A1);
    prettyPrint(A1);

    printf("\n\n");
    clear(A1);
    return 0;
}

int main () {
    sorting_tests();
    return 0;
}