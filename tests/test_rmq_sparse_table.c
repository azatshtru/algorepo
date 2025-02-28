#include "../headers/rmq_sparse_table.h"
#include "orange_juice.h"
#include "../headers/logging.h"

oj_test(test_construction_of_sparse_table_from_an_array) {
    int array[8] = { 1, 3, 4, 8, 6, 1, 4, 2 };
    int** table = sparse_table_new(8, array);
    log_label("can");
    sparse_table_print(table, 8);

    int sparse_table_column_2[8] = { 1, 3, 4, 6, 1, 1, 2 };
    int sparse_table_column_3[8] = { 1, 3, 1, 1, 1 };


    oj_assert_eq_bytes(8 * sizeof(int), array, table[0], "");
    oj_assert_eq_bytes(7 * sizeof(int), sparse_table_column_2, table[1], "");
    oj_assert_eq_bytes(5 * sizeof(int), sparse_table_column_3, table[2], "");

    sparse_table_free(table, 8);
    oj_fresh;
}

oj_test(test_minimum_query_using_sparse_table) {
    int array[8] = { 1, 3, 4, 8, 6, 1, 4, 2 };
    int** table = sparse_table_new(8, array);
    sparse_table_init(table, 8, array);

    oj_assert_eq_int(1, sparse_table_minimum(1, 6, table));
    oj_assert_eq_int(3, sparse_table_minimum(1, 4, table));

    sparse_table_free(table, 8);

    oj_fresh;
}

oj_prepare(rmq_sparse_table_tests) {
    oj_run(test_construction_of_sparse_table_from_an_array);
    oj_run(test_minimum_query_using_sparse_table);
    oj_report;
    oj_fresh;
}

int main() {
    oj_blend(rmq_sparse_table_tests, 0);
    return 0;
}
