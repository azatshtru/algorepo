#include "miniqutils.h"

#ifndef MIN_SPARSE_TABLE
#define MIN_SPARSE_TABLE

int sparse_table_min_q(int* array, int a, int b, int** table);
int** sparse_table_new(int len, int* array);
int sparse_table_free(int** table, int len);
int sparse_table_init(int** table, int len, int* array);
int sparse_table_print(int** table, int len);
int sparse_table_minimum(int len, int* array, int a, int b, int** table);

#endif
