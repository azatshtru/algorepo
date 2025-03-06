#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int rows, cols;
    int** matrix;
    int** tree;
} simple_2d_segment_tree;

int** simple_2d_segment_tree_allocate(int size_x, int size_y) {
    int** arr = malloc(size_x * sizeof(int*));
    for (int i = 0; i < size_x; i++) {
        arr[i] = malloc(size_y * sizeof(int));
        memset(arr[i], 0, size_y * sizeof(int));
    }
    return arr;
}

void simple_2d_segment_tree_build_y(simple_2d_segment_tree* st, int node_x, int start_x, int end_x, int node_y, int start_y, int end_y) {
    if (start_y == end_y) {
        if (start_x == end_x) {
            st->tree[node_x][node_y] = st->matrix[start_x][start_y];
        } else {
            st->tree[node_x][node_y] = st->tree[2 * node_x + 1][node_y] + st->tree[2 * node_x + 2][node_y];
        }
    } else {
        int mid_y = (start_y + end_y) / 2;
        simple_2d_segment_tree_build_y(st, node_x, start_x, end_x, 2 * node_y + 1, start_y, mid_y);
        simple_2d_segment_tree_build_y(st, node_x, start_x, end_x, 2 * node_y + 2, mid_y + 1, end_y);
        st->tree[node_x][node_y] = st->tree[node_x][2 * node_y + 1] + st->tree[node_x][2 * node_y + 2];
    }
}

void simple_2d_segment_tree_build_x(simple_2d_segment_tree* st, int node_x, int start_x, int end_x) {
    if (start_x == end_x) {
        simple_2d_segment_tree_build_y(st, node_x, start_x, end_x, 0, 0, st->cols - 1);
    } else {
        int mid_x = (start_x + end_x) / 2;
        simple_2d_segment_tree_build_x(st, 2 * node_x + 1, start_x, mid_x);
        simple_2d_segment_tree_build_x(st, 2 * node_x + 2, mid_x + 1, end_x);
        simple_2d_segment_tree_build_y(st, node_x, start_x, end_x, 0, 0, st->cols - 1);
    }
}

int simple_2d_segment_tree_query_y(simple_2d_segment_tree* st, int node_x, int node_y, int start_y, int end_y, int ly, int ry) {
    if (ly > ry) return 0;
    if (start_y == ly && end_y == ry) return st->tree[node_x][node_y];

    int mid_y = (start_y + end_y) / 2;
    return simple_2d_segment_tree_query_y(st, node_x, 2 * node_y + 1, start_y, mid_y, ly, ry < mid_y ? ry : mid_y) +
           simple_2d_segment_tree_query_y(st, node_x, 2 * node_y + 2, mid_y + 1, end_y, ly > mid_y ? ly : mid_y + 1, ry);
}

int simple_2d_segment_tree_query_x(simple_2d_segment_tree* st, int node_x, int start_x, int end_x, int lx, int rx, int ly, int ry) {
    if (lx > rx) return 0;
    if (start_x == lx && end_x == rx) return simple_2d_segment_tree_query_y(st, node_x, 0, 0, st->cols - 1, ly, ry);

    int mid_x = (start_x + end_x) / 2;
    return simple_2d_segment_tree_query_x(st, 2 * node_x + 1, start_x, mid_x, lx, rx < mid_x ? rx : mid_x, ly, ry) +
           simple_2d_segment_tree_query_x(st, 2 * node_x + 2, mid_x + 1, end_x, lx > mid_x ? lx : mid_x + 1, rx, ly, ry);
}

void simple_2d_segment_tree_update_y(simple_2d_segment_tree* st, int node_x, int start_x, int end_x, int node_y, int start_y, int end_y, int y, int diff) {
    if (start_y == end_y) {
        st->tree[node_x][node_y] += diff;
    } else {
        int mid_y = (start_y + end_y) / 2;
        if (y <= mid_y) {
            simple_2d_segment_tree_update_y(st, node_x, start_x, end_x, 2 * node_y + 1, start_y, mid_y, y, diff);
        } else {
            simple_2d_segment_tree_update_y(st, node_x, start_x, end_x, 2 * node_y + 2, mid_y + 1, end_y, y, diff);
        }
        st->tree[node_x][node_y] = st->tree[node_x][2 * node_y + 1] + st->tree[node_x][2 * node_y + 2];
    }
}

void simple_2d_segment_tree_update_x(simple_2d_segment_tree* st, int node_x, int start_x, int end_x, int x, int y, int value) {
    if (start_x == end_x) {
        simple_2d_segment_tree_update_y(st, node_x, start_x, end_x, 0, 0, st->cols - 1, y, value);
    } else {
        int mid_x = (start_x + end_x) / 2;
        if (x <= mid_x) {
            simple_2d_segment_tree_update_x(st, 2 * node_x + 1, start_x, mid_x, x, y, value);
        } else {
            simple_2d_segment_tree_update_x(st, 2 * node_x + 2, mid_x + 1, end_x, x, y, value);
        }
        simple_2d_segment_tree_update_y(st, node_x, start_x, end_x, 0, 0, st->cols - 1, y, value);
    }
}

void simple_2d_segment_tree_update(simple_2d_segment_tree* st, int x, int y, int new_value) {
    int diff = new_value - st->matrix[x][y];
    st->matrix[x][y] = new_value;
    simple_2d_segment_tree_update_x(st, 0, 0, st->rows - 1, x, y, diff);
}

int simple_2d_segment_tree_query(simple_2d_segment_tree* st, int lx, int ly, int rx, int ry) {
    return simple_2d_segment_tree_query_x(st, 0, 0, st->rows - 1, lx, rx, ly, ry);
}

void simple_2d_segment_tree_free(simple_2d_segment_tree* st) {
    for (int i = 0; i < 4 * st->rows; i++) free(st->tree[i]);
    free(st->tree);
    for (int i = 0; i < st->rows; i++) free(st->matrix[i]);
    free(st->matrix);
}

int main() {
    int rows = 4, cols = 4;
    int mat[4][4] = {
        {7, 6, 1, 6},
        {8, 7, 5, 2},
        {3, 9, 7, 1},
        {8, 5, 3, 8}
    };

    simple_2d_segment_tree st;
    st.rows = rows;
    st.cols = cols;
    st.matrix = simple_2d_segment_tree_allocate(rows, cols);
    st.tree = simple_2d_segment_tree_allocate(4 * rows, 4 * cols);

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            st.matrix[i][j] = mat[i][j];
        }
    }

    simple_2d_segment_tree_build_x(&st, 0, 0, rows - 1);

    printf("sum of submatrix (1, 1) to (2, 3) -> %d\n", simple_2d_segment_tree_query(&st, 1, 1, 2, 3));

    simple_2d_segment_tree_update(&st, 1, 1, 10);
    printf("sum of submatrix (1, 1) to (2, 3) after update -> %d\n", simple_2d_segment_tree_query(&st, 1, 1, 2, 3));

    simple_2d_segment_tree_free(&st);
    return 0;
}

