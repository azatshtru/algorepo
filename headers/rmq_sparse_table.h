#include "miniqutils.h"

#ifndef RMQ_SPARSE_TABLE
#define RMQ_SPARSE_TABLE

struct rmq_sparse_table_entry {
    int v;
    int i;
};

typedef struct rmq_sparse_table_entry RMQSparseTableEntry;
typedef RMQSparseTableEntry** RMQSparseTable;

RMQSparseTableEntry** sparse_table_new(int len, int* array);
int sparse_table_free(RMQSparseTableEntry** table, int len);
int sparse_table_init(RMQSparseTableEntry** table, int len, int* array);
int sparse_table_print(RMQSparseTableEntry** table, int len);
RMQSparseTableEntry sparse_table_minimum(int a, int b, RMQSparseTableEntry** table);

#endif
