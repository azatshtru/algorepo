#include "headers/logging.h"

int main() {
    int a[10] = { 5, 6, 1, 2, 7, 8, 9, 0, 4, 12 };
    log_array(a, int, 10, x, printf("%d", x));
    log_label("watermelon");
    log_float("damn", 5.0);
    log_int("damn", 5);
    return 0;

}
