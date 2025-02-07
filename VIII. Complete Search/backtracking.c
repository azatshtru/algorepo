#include <stdlib.h>

//Backtracking recursively constructs solutions following a certain rule starting from nothing.
//If the rule is broken in any solution, no recursion is performed further and no further solutions are generated on the same recursive path.
//Following example solves the n-queen problem using backtracking.

typedef struct nxnChessboard {
    int* column;
    int* diag1;
    int* diag2;
} nChessboard;

nChessboard* setNxNChessboard(int n) {
    nChessboard* board = (nChessboard*)malloc(sizeof(nChessboard));
    board->column=(int*)malloc(n*sizeof(int)); 
    board->diag1=(int*)malloc((2*n-1)*sizeof(int)); 
    board->diag2=(int*)malloc((2*n-1)*sizeof(int)); 
    for(int i = 0; i < n; i++) { *(board->column+i) = 0; }
    for(int i = 0; i < (2*n-1); i++) { *(board->diag1+i) = *(board->diag2+i) = 0; }
    return board;
}

int nQueens(int n, int y) {
    static int count = 0;
    static nChessboard* board = NULL; 
    if(board==NULL){ board=setNxNChessboard(n); }

    if(y==n) { return ++count; }
    for(int x = 0; x < n; x++) {
        int* columns = board->column;
        int* diag1 = board->diag1;
        int* diag2 = board->diag2;
        if(*(columns+x) || *(diag1+x+y) || *(diag2+n+x-y-1)) { continue; }
        *(columns+x) = *(diag1+x+y) = *(diag2+n+x-y-1) = 1;
        nQueens(n, y+1);
        *(columns+x) = *(diag1+x+y) = *(diag2+n+x-y-1) = 0;
    }
    return count;
}