#include "../headers/miniqutils.h"

#define EULER_CONSTANT 2.718281828459045235
#define PI 3.14159265358979323846

float negative_infinity() {
    union {
        int i;
        float f;
    } u;
    u.i = 0xFF800000; // IEEE 754 representation of -Infinity for a 32-bit float
    return u.f;
}

int positive_mod(int a, int m) {
    return (a % m + m) % m;
}

int close_to_zero(float epsilon) {
    if(epsilon < 1e-4 && epsilon > -1e-4) {
        return 1;
    }
    return 0;
}

double natural_log(double x) {
    if(x <= 0) {
        return 0.0/0.0;
    }

    if (x == 1.0) {
        return 0.0;
    }

    int invert = 0;
    if(x < 1.0) {
        x = 1.0 / x;
        invert = 1;
    }

    int scale = 0;
    while(x > EULER_CONSTANT) {
        x /= EULER_CONSTANT;
        ++scale;
    }

    x -= 1.0;

    double term = x;
    double result = 0.0;
    double power = x;

    for(int n = 1; n < 100; n++) {
        if (n > 1) {
            power *= x;
        }
        term = power / n;
        result += (n % 2 == 0) ? -term : term;
        if (term < 1e-10) {
            break;
        }
    }

    result += scale;
    return invert ? -result : result;
}
