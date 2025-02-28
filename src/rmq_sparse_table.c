#include "../headers/rmq_sparse_table.h"

int** sparse_table_new(int len, int* array) {
    int log = log_2(len) + 1;
    int** table = malloc(log * sizeof(int*));
    for(int i = 0; i < log + 1; i++) {
        table[i] = malloc(sizeof(int) * (len - (1 << i) + 1));
    }
    sparse_table_init(table, len, array);
    return table;
}

int sparse_table_free(int** table, int len) {
    int log = log_2(len) + 1;
    for(int i = 0; i < log; i++) {
        free(table[i]);
    }
    free(table);
    return 0;
}

int sparse_table_init(int** table, int len, int* array) {
    int log = log_2(len) + 1;

    for(int j = 0; j < len; j++) {
        table[0][j] = array[j];
    }

    for(int i = 1; i < log; i++) {
        for(int j = 0; j < len - (1 << i) + 1; j++) {
            table[i][j] = min_i(2, table[i - 1][j], table[i - 1][j + (1 << (i - 1))]);
        }
    }
    return 0;
}

int sparse_table_print(int** table, int len) {
    int log = log_2(len) + 1;
    printf("sparse_table![[\n");
    for(int i = 0; i < log; i++) {
        for(int j = 0; j < len - (1 << i) + 1; j++) {
            printf("%d, ", table[i][j]);
        }
        printf("\n");
    }
    printf("]]\n");
    return 0;
}

int sparse_table_minimum(int a, int b, int** table) {
    if(table == NULL) return 0;
    int log = log_2(b - a + 1);
    return min_i(2, table[log][a], table[log][b - (1 << log) + 1]);
}

// the "Method of Four Russians" can be used to further improve the precompute time and space complexity to O(n)
