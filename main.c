#include <stdio.h>
#include "headers/miniqutils.h"

int main() {
    int k = min_f(10, 5, 6, 1, 2, 7, 8, 9, 0, 4, 12, 11);
    printf("%d\n", k);
    return 0;
}
