#include <limits.h>
#include <string.h>

#ifndef MINIQUTILS
#define MINIQUTILS

void memzero(void* array, int len);
int power(int base, int exponent);
void swap(void* a, void* b, unsigned int size);
int cantor_pairing(int a, int b);
float negative_infinity();
int positive_mod(int a, int m);
int close_to_zero(float epsilon);
double natural_log(double x);

#define I32_MIN -2147483648
#define I32_MAX 2147483647

#define container_from_ptr(type, ptr, member_name) ((type*)(ptr - (unsigned long)(&(((type*)0)->member_name))))

#endif
