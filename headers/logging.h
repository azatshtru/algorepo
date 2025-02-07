#include <stdio.h>

#ifndef LOGGING
#define LOGGING

#define log_int(label, x) printf("[%s, %d] %s -> %d\n", __FILE__, __LINE__, label, x)
#define log_float(label, x) printf("[%s, %d] %s -> %f\n", __FILE__, __LINE__, label, x)
#define log_label(label) printf("[%s, %d] %s\n", __FILE__, __LINE__, label)
#define log_pointer(label, x) printf("[%s, %d] %s -> %p\n", __FILE__, __LINE__, label, x)

#define log_array(array, type, len, x, print_ins) do {  \
    printf("[%s, %d]\n", __FILE__, __LINE__);           \
    for(int i = 0; i < len; i++) {                      \
        printf("  %d -> ", i);                          \
        type x = array[i];                              \
        print_ins;                                      \
        printf("\n");                                   \
    }                                                   \
} while(0)                                              \

#endif
