#include <stdio.h>
#include "../headers/miniqutils.h"

/// O(n4^{2m}) implementation

// < left tile piece
// > right tile piece
// ^ up tile piece
// V low tile piece
char tilepiece[4] = { '<', '>', '^', 'V' };

int tilings_row_print(char* row, int dim_x) {
    for(int x = 0; x < dim_x; x++) {
        printf("%c, ", row[x]);
    }
    printf("\n");
    return 0;
}

void tilings_nth_row(char* row, int dim_x, int n) {
    for(int i = dim_x - 1; i >= 0; i--) {
        int j = n % 4;
        n = n / 4;
        row[i] = tilepiece[j];
    }
}

int tilings_row_contains_invalid_tile(char* row, int dim_x, char invalid_tile) {
    for(int i = 0; i < dim_x; i++) {
        if(row[i] == invalid_tile) { return 1; }
    }
    return 0;
}

int tilings_row_is_valid(char* row, int dim_x) {
    if(row[0] == '>') { return 0; }
    if(row[dim_x - 1] == '<') { return 0; }
    for(int i = 1; i < dim_x; i++) {
        if(row[i] == '>' && row[i-1] != '<') { return 0; }
        if(row[i] != '>' && row[i-1] == '<') { return 0; }
    }
    return 1;
}

int tilings_rows_are_compatible(int dim_x, char* row_1, char* row_2) {
    if(!tilings_row_is_valid(row_1, dim_x) || !tilings_row_is_valid(row_2, dim_x)) {
        return 0;
    }
    for(int i = 0; i < dim_x; i++) {
        if(row_1[i] == '^' && row_2[i] != 'V') { return 0; }
        if(row_1[i] != '^' && row_2[i] == 'V') { return 0; }
    }
    return 1;
}

int counting_tilings(int dim_x, int dim_y) {
    if(dim_x > dim_y) {
        dim_x = dim_x ^ dim_y;
        dim_y = dim_x ^ dim_y;
        dim_x = dim_x ^ dim_y;
    }

    int permutations = power(4, dim_x);
    int states[2][permutations];
    memzero(states[0], permutations*sizeof(int));
    memzero(states[1], permutations*sizeof(int));


    for(int i = 0; i < permutations; i++) {
        char row[dim_x];
        tilings_nth_row(row, dim_x, i);
        if(!tilings_row_contains_invalid_tile(row, dim_x, 'V') && tilings_row_is_valid(row, dim_x)) {
            states[0][i] = 1;
        }
    }

    for(int y = 1; y < dim_y; y++) {
        for(int i = 0; i < permutations; i++) {
            if(states[0][i] == 0) {
                continue;
            }
            char row_1[dim_x];
            tilings_nth_row(row_1, dim_x, i);
            for(int j = 0; j < permutations; j++) {
                char row_2[dim_x];
                tilings_nth_row(row_2, dim_x, j);
                if(y == dim_y-1 && tilings_row_contains_invalid_tile(row_2, dim_x, '^')) {
                    continue;
                }
                if(tilings_rows_are_compatible(dim_x, row_1, row_2)) {
                    states[1][j] += states[0][i];
                }
            }
        }
        memcpy(states[0], states[1], permutations*sizeof(int));
        memzero(states[1], permutations*sizeof(int));
    }

    int sum = 0;
    for(int i = 0; i < permutations; i++) {
        sum += states[0][i];
    }

    return sum;
}

// there is also a direct formula for calculating tilings which works in O(nm).
// $$\prod_{a=1}^{n/2}\prod_{b=1}^{m/2}4(cos^2\frac{\pi a}{n+1}+cos^2\frac{\pi b}{m+1})$$

#include "../tests/orange_juice.h"

oj_test(tilings_nth_row_returns_the_correct_row) {
    char row[10];
    tilings_nth_row(row, 10, 22);
    oj_assert_eq_bytes(10, "<<<<<<<>>^", row, "");
    oj_fresh;
}

oj_test(tilings_row_is_valid_returns_0_for_invalid_row) {
    char row[10];
    tilings_nth_row(row, 10, 22);
    int result = tilings_row_is_valid(row, 10);
    oj_assert_eq_int(0, result);
    oj_fresh;
}

oj_test(tilings_row_is_valid_returns_1_for_valid_row) {
    char row[4];
    tilings_nth_row(row, 4, 17);
    int result = tilings_row_is_valid(row, 4);
    oj_assert_eq_int(1, result);
    oj_fresh;
}

oj_test(tilings_rows_are_compatible_returns_1_for_compatible_rows) {
    char row_1[8] = "<>^V^<>V";
    char row_2[8] = "<>V^V^<>";
    int result = tilings_rows_are_compatible(8, row_1, row_2);
    oj_assert_eq_int(1, result);
    oj_fresh;
}

oj_test(tilings_rows_are_compatible_returns_0_for_incompatible_rows) {
    char row_1[8] = "<>^V^<>V";
    char row_2[8] = "<>V^VV<>";
    int result = tilings_rows_are_compatible(8, row_1, row_2);
    oj_assert_eq_int(0, result);
    oj_fresh;
}

oj_test(tilings_rows_are_compatible_returns_0_for_invalid_rows) {
    char row_1[8] = "<>^V^<>V";
    char row_2[8] = ">>V^V^<>";
    int result = tilings_rows_are_compatible(8, row_1, row_2);
    oj_assert_eq_int(0, result);
    oj_fresh;
}

oj_test(counting_tilings_returns_2_for_2x2_grid) {
    int result = counting_tilings(2, 2);
    oj_assert_eq_int(2, result);
    oj_fresh;
}

oj_test(counting_tilings_returns_781_for_4x7_grid) {
    int result = counting_tilings(4, 7);
    oj_assert_eq_int(781, result);
    oj_fresh;
}

oj_test(counting_tilings_returns_789797918_for_10x1000_grid) {
    oj_assert_eq_int(789797918, counting_tilings(10, 1000));
    oj_fresh;
}

// run only if you have some time to kill
oj_test(counting_tilings_for_various_grids) {
    oj_assert_eq_int(391705009, counting_tilings(8, 123));
    oj_assert_eq_int(0, counting_tilings(9, 999));
    oj_assert_eq_int(296820210, counting_tilings(9, 1000));
    oj_assert_eq_int(449662393, counting_tilings(10, 500));
    oj_assert_eq_int(709630856, counting_tilings(10, 999));
    oj_assert_eq_int(217283915, counting_tilings(7, 50));
    oj_assert_eq_int(281, counting_tilings(6, 4));
    oj_fresh;
}

oj_prepare(test_counting_tilings_row_validity) {
    oj_run(tilings_row_is_valid_returns_0_for_invalid_row);
    oj_run(tilings_row_is_valid_returns_1_for_valid_row);
    oj_run(tilings_rows_are_compatible_returns_0_for_incompatible_rows);
    oj_run(tilings_rows_are_compatible_returns_1_for_compatible_rows);
    oj_run(tilings_rows_are_compatible_returns_0_for_invalid_rows);
    oj_report;
    oj_fresh;
}

oj_prepare(test_counting_tilings) {
    oj_run(tilings_nth_row_returns_the_correct_row);
    oj_run(counting_tilings_returns_2_for_2x2_grid);
    oj_run(counting_tilings_returns_781_for_4x7_grid);
    oj_report;
    oj_fresh;
}

int main() {
    oj_blend(test_counting_tilings_row_validity, 0);
    oj_blend(test_counting_tilings, 0);
    return 0;
}
