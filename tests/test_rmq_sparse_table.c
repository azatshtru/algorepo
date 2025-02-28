#include "../headers/rmq_sparse_table.h"
#include "orange_juice.h"
#include "../headers/logging.h"

oj_test(test_minimum_query_using_sparse_table) {
    int array[8] = { 1, 3, 4, 8, 6, 1, 4, 2 };
    RMQSparseTable table = sparse_table_new(8, array);
    sparse_table_print(table, 8);

    oj_assert_eq_int(1, sparse_table_minimum(1, 6, table).v);
    oj_assert_eq_int(3, sparse_table_minimum(1, 4, table).v);

    sparse_table_free(table, 8);

    oj_fresh;
}

oj_prepare(rmq_sparse_table_tests) {
    oj_run(test_minimum_query_using_sparse_table);
    oj_report;
    oj_fresh;
}

int main() {
    oj_blend(rmq_sparse_table_tests, 0);
    return 0;
}
