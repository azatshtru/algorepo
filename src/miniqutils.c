#include "../headers/miniqutils.h"
#include <stdio.h>

double min_f(int n, ...) {
    va_list args;
    va_start(args, n);
    double minimum = va_arg(args, double);
    
    for(int i = 1; i < n; i++) {
        double x = va_arg(args, double);
        minimum = x < minimum ? x : minimum;
    }

    va_end(args);
    return minimum;
}

int min_i(int n, ...) {
    va_list args;
    va_start(args, n);
    int minimum = va_arg(args, int);
    
    for(int i = 1; i < n; i++) {
        int x = va_arg(args, int);
        minimum = x < minimum ? x : minimum;
    }

    va_end(args);
    return minimum;
}

void memzero(void* array, int len) {
    memset(array, 0, len);
}

int power(int base, int exponent) {
    int x = 1;
    for(int i = 0; i < exponent; i++) {
        x *= base;
    }
    return x;
}

void swap(void* a, void* b, unsigned int size) {
    char temp[size];
    memzero(temp, size);
    memmove(temp, a, size);
    memmove(a, b, size);
    memmove(b, temp, size);
}

int log_2(int x) {
    int log = 0;
    while(x>>=1) {
        ++log;
    }
    return log; 
}

int cantor_pairing(int a, int b) {
    return ((a+b)*(a+b+1))/2 + b;
}

float positive_infinity() {
    union raw_float positive_infinity_IEEE745;
    positive_infinity_IEEE745.u = 0x7F800000; // IEEE 754 representation of +Infinity for 32-bit float
    return positive_infinity_IEEE745.f;
}

float negative_infinity() {
    union raw_float negative_infinity_IEEE745;
    negative_infinity_IEEE745.u = 0xFF800000; // IEEE 754 representation of -Infinity for 32-bit float
    return negative_infinity_IEEE745.f;
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

void euro_coins(int* coins) {
    int i = 0;
    coins[0] = 1;
    coins[1] = 2;
    coins[2] = 5;
    coins[3] = 10;
    coins[4] = 20;
    coins[5] = 50;
}
