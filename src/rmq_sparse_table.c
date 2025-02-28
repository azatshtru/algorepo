#include "../headers/rmq_sparse_table.h"
#include "../headers/logging.h"

RMQSparseTableEntry** sparse_table_new(int len, int* array) {
    int log = log_2(len) + 1;
    RMQSparseTableEntry** table = malloc(log * sizeof(RMQSparseTableEntry*));
    for(int i = 0; i < log + 1; i++) {
        table[i] = malloc(sizeof(RMQSparseTableEntry) * (len - (1 << i) + 1));
    }
    sparse_table_init(table, len, array);
    return table;
}

int sparse_table_free(RMQSparseTableEntry** table, int len) {
    int log = log_2(len) + 1;
    for(int i = 0; i < log; i++) {
        free(table[i]);
    }
    free(table);
    return 0;
}

int sparse_table_init(RMQSparseTableEntry** table, int len, int* array) {
    int log = log_2(len) + 1;

    for(int j = 0; j < len; j++) {
        table[0][j].v = array[j];
        table[0][j].i = j;
    }

    for(int i = 1; i < log; i++) {
        for(int j = 0; j < len - (1 << i) + 1; j++) {
            RMQSparseTableEntry a = table[i - 1][j];
            RMQSparseTableEntry b = table[i - 1][j + (1 << (i - 1))];
            table[i][j] = a.v < b.v ? a : b;
        }
    }
    return 0;
}

int sparse_table_print(RMQSparseTableEntry** table, int len) {
    int log = log_2(len) + 1;
    printf("sparse_table![[\n");
    for(int i = 0; i < log; i++) {
        for(int j = 0; j < len - (1 << i) + 1; j++) {
            printf("%d, ", table[i][j].v);
        }
        printf("\n");
    }
    printf("]]\n");
    return 0;
}

RMQSparseTableEntry sparse_table_minimum(int a, int b, RMQSparseTableEntry** table) {
    int log = log_2(b - a + 1);
    RMQSparseTableEntry x = table[log][a];
    RMQSparseTableEntry y = table[log][b - (1 << log) + 1];
    return x.v < y.v ? x : y;
}

// the "Method of Four Russians" can be used to further improve the precompute time and space complexity to O(n)
