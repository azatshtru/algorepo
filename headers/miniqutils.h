#include <limits.h>
#include <string.h>
#include <stdarg.h>

#ifndef MINIQUTILS
#define MINIQUTILS

union raw_float {
    unsigned int u;
    float f;
};

double min_f(int n, ...);
int min_i(int n, ...);
void memzero(void* array, int len);
int power(int base, int exponent);
void swap(void* a, void* b, unsigned int size);
int log_2(int x);
int cantor_pairing(int a, int b);
float positive_infinity();
float negative_infinity();
int positive_mod(int a, int m);
int close_to_zero(float epsilon);
double natural_log(double x);
void euro_coins(int* coins);

#define I32_MIN -2147483648
#define I32_MAX 2147483647

#define container_of(ptr, type, member_name) ((type*)((char*)ptr - (unsigned long)(&(((type*)0)->member_name))))

#endif
