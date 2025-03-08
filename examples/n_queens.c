#include <stdio.h>
#include <stdlib.h>

// backtracking recursively constructs solutions following a certain rule starting from nothing
// if the rule is broken in any solution, no recursion is performed further and no further solutions are generated on the same recursive path

struct nxnChessboard {
    int* column;
    int* diag1;
    int* diag2;
};

struct nxnChessboard* buildNxNChessboard(int n) {
    struct nxnChessboard* board = (struct nxnChessboard*)malloc(sizeof(struct nxnChessboard));
    board->column = malloc(n * sizeof(int)); 
    board->diag1 = malloc((2 * n - 1) * sizeof(int)); 
    board->diag2 = malloc((2 * n - 1) * sizeof(int)); 
    for(int i = 0; i < n; i++) {
        board->column[i] = 0;
    }
    for(int i = 0; i < (2 * n - 1); i++) {
        board->diag1[i] = board->diag2[i] = 0;
    }
    return board;
}

void freeNxNChessboard(struct nxnChessboard* board) {
    free(board->column); 
    free(board->diag1);
    free(board->diag2);
}

int nQueens(struct nxnChessboard* board, int* count, int n, int y) {
    if(y == n) return ++*count;
    for(int x = 0; x < n; x++) {
        int* columns = board->column;
        int* diag1 = board->diag1;
        int* diag2 = board->diag2;
        if(columns[x] || diag1[x+y] || diag2[n+x-y-1]) continue;
        columns[x] = diag1[x+y] = diag2[n+x-y-1] = 1;
        nQueens(board, count, n, y+1);
        columns[x] = diag1[x+y] = diag2[n+x-y-1] = 0;
    }
    return *count;
}

int main() {
    int n = 8;
    struct nxnChessboard* board = buildNxNChessboard(n);
    int count = 0;
    printf("%d queens: %d", n, nQueens(board, &count, n, 0));
    freeNxNChessboard(board);
    return 0;
}
