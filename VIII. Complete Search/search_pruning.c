#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//Pruning the search by noticing common patterns to determine if the search cannot continue further in a backtracking algorithm can heavily optimize the running time.
//This is demonstrated here by calculating the total number of paths in an nxn grid from one corner to its opposite corner such that each square is visited only once.
//This begins with a naive algorithm with no pruning and then pruning is done in 4 levels. 

int* initNxNGrid(int n) {
    int* grid=(int*)malloc((n*n+1)*sizeof(int));
    *grid = n;
    for(int i = 1; i < (n*n+1); i++) { *(grid+i) = 0; }
    return grid;
}

int setXY(int* grid, int x, int y) {
    int n = *grid;
    *(grid+y*n+x+1) = 1;
    return 0;
}

int unsetXY(int* grid, int x, int y) {
    int n = *grid;
    *(grid+y*n+x+1) = 0;
    return 0;
}

int getXY(int* grid, int x, int y) {
    int n = *grid;
    return *(grid+y*n+x+1);
}

int nxnPaths_0(int n, int x, int y) {
    static int count = 0;
    static int fill = 0;
    static int* grid = NULL;
    if(grid==NULL) { grid = initNxNGrid(n); }

    if(fill==n*n-1 && x==n-1 && y==n-1) { return ++count; }
    if(x==n-1 && y==n-1) { return count; }
    if(x>n-1 || y>n-1) { return count; }
    if(x<0 || y<0) { return count; }
    if(getXY(grid, x, y)) { return count; }
    setXY(grid, x, y);
    fill+=1;
    nxnPaths_0(n, x+1, y);
    nxnPaths_0(n, x-1, y);
    nxnPaths_0(n, x, y+1);
    nxnPaths_0(n, x, y-1);
    unsetXY(grid, x, y);
    fill-=1;
    return count;
}

//A large optimization can be made upon noticing the fact that if the algorithm can only take two supplementary opposite paths then the board is effectively split into two...
//... and filling one part of board will require overlapping to go to the other part, hence the algorithm need not to check further since it cannot continue.

int checkGridSplit(int* grid, int x, int y) {
    int p = 0;
    int q = 0;
    int n = *grid;
    if(x+1>n-1 || getXY(grid, x+1, y)) { p++; }
    if(x-1<0 || getXY(grid, x-1, y)) { p++; }
    if(y+1>n-1 || getXY(grid, x, y+1)) { q++; }
    if(y-1<0 || getXY(grid, x, y-1)) { q++; }
    if((p==2 && q==0) || (p==0 && q==2)) { return 1; }
    return 0;
}

int nxnPaths_1(int n, int x, int y) {
    static int count = 0;
    static int fill = 0;
    static int* grid = NULL;
    if(grid==NULL) { grid = initNxNGrid(n); }

    if(fill==n*n-1 && x==n-1 && y==n-1) { return ++count; }
    if(x==n-1 && y==n-1) { return count; }
    if(x>n-1 || y>n-1) { return count; }
    if(x<0 || y<0) { return count; }
    if(getXY(grid, x, y)) { return count; }
    if(checkGridSplit(grid, x, y)) { return count; }
    setXY(grid, x, y);
    fill+=1;
    nxnPaths_1(n, x+1, y);
    nxnPaths_1(n, x-1, y);
    nxnPaths_1(n, x, y+1);
    nxnPaths_1(n, x, y-1);
    unsetXY(grid, x, y);
    fill-=1;
    return count;
}

//The time to search can be halved by considering one starting direction, since every other path is basically mirror image across the principal diagonal.

int nxnPaths_2(int n, int x, int y) {
    static int count = 0;
    static int fill = 1;
    static int* grid = NULL;
    if(grid==NULL) { 
        grid = initNxNGrid(n);
        setXY(grid, 0, 0);
        nxnPaths_2(n, 1, 0);
    }

    if(fill==n*n-1 && x==n-1 && y==n-1) { return ++count; }
    if(x==n-1 && y==n-1) { return 2*count; }
    if(x>n-1 || y>n-1) { return 2*count; }
    if(x<0 || y<0) { return 2*count; }
    if(getXY(grid, x, y)) { return 2*count; }
    if(checkGridSplit(grid, x, y)) { return 2*count; }
    setXY(grid, x, y);
    fill+=1;
    nxnPaths_2(n, x+1, y);
    nxnPaths_2(n, x-1, y);
    nxnPaths_2(n, x, y+1);
    nxnPaths_2(n, x, y-1);
    unsetXY(grid, x, y);
    fill-=1;
    return 2*count;
}

int nxnPathsBenchmark(int n) {
    clock_t begin = clock();
    printf("\nNo Optimization: %d\n", nxnPaths_0(n, 0, 0));
    printf("time taken: %.2f seconds\n", (float)(clock()-begin)/CLOCKS_PER_SEC);
    printf("\n-----------------");
    begin = clock();
    printf("\nOptimization 1: %d\n", nxnPaths_1(n, 0, 0));
    printf("time taken: %.2f seconds\n", (float)(clock()-begin)/CLOCKS_PER_SEC);
    printf("\n-----------------");
    begin = clock();
    printf("\nOptimization 2: %d\n", nxnPaths_2(n, 0, 0));
    printf("time taken: %.2f seconds\n", (float)(clock()-begin)/CLOCKS_PER_SEC);
    printf("\n");
    return 0;
}