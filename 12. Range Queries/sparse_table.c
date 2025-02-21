#include "../headers/miniqutils.h"

int sparse_table_min_q(int* array, int a, int b, int** table) {
    if(table[log_2(b - a + 1)][a]) {
        return table[log_2(b - a + 1)][a];
    }
    int w = (b - a + 1) / 2;
    int x;
    if(a == b) {
        x = array[a];
    } else {
        x = min_i(
            sparse_table_min_q(array, a, a + w - 1, table),
            sparse_table_min_q(array, a + w, b, table)
        );
    }
    table[log_2(b - a + 1)][a] = x;
    return x;
}

int** sparse_table_new(int len, int* array) {
    int log = log_2(len);
    int** table = malloc((1 + log) * sizeof(int*));
    for(int i = 0; i < log; i++) {
        table[i] = malloc(sizeof(int) * (len - power(2, i) + 1));
    }
    return table;
}

int sparse_table_free(int** table, int len) {
    int log = log_2(len);
    for(int i = 0; i < log; i++) {
        free(table[i]);
    }
    free(table);
    return 0;
}

int sparse_table_init(int** table, int len, int* array) {
    int p = log_2(len);
    for(int i = 0; i < p; i++) {
        for(int j = 0; j < len - power(2, i) + 1; j++) {
            sparse_table_min_q(array, j, j + power(2, i) - 1, table);
        }
    }
    return 0;
}

int sparse_table_print(int** table, int len) {
    int log = log_2(len);
    printf("sparse_table![[\n");
    for(int i = 0; i < log; i++) {
        for(int j = 0; j < len - power(2, i) + 1; j++) {
            printf("%d, ", table[i][j]);
        }
        printf("\n");
    }
    printf("]]\n");
    return 0;
}

int sparse_table_minimum(int len, int* array, int a, int b, int** table) {
    if(table == NULL) return 0;
    int log = log_2(b - a + 1);
    int k = power(2, log);
    int x = min_i(
        sparse_table_min_q(array, a, a + k - 1, table),
        sparse_table_min_q(array, b - k + 1, b, table)
    );
    return x;
}
