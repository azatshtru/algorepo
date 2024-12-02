#include "../headers/miniqutils.h"

int positive_mod(int a, int m) {
    return (a % m + m) % m;
}

int close_to_zero(float epsilon) {
    if(epsilon < 0.00001 && epsilon > -0.00001) {
        return 1;
    }
    return 0;
}
