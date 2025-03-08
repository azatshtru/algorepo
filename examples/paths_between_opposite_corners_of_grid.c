#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// pruning the search by noticing common patterns to determine if the search cannot
// continue further in a backtracking algorithm can heavily optimize the running time
//
// this is demonstrated here by calculating the total number of paths in an nxn grid
// from one corner to its opposite corner such that each square is visited only once
//
// this begins with a naive algorithm with no pruning and then pruning is done in 3 levels

int paths_between_opposite_corners_optimization_0(int** grid, int* count, int fill, int n, int x, int y) {
    if(fill == n * n - 1 && x == n - 1 && y == n - 1) return ++*count;
    if(x == n - 1 && y == n - 1) return *count;
    if(x > n - 1 || y > n - 1) return *count;
    if(x < 0 || y < 0) return *count;
    if(grid[x][y]) return *count;
    grid[x][y] = 1;
    fill += 1;
    paths_between_opposite_corners_optimization_0(grid, count, fill, n, x+1, y);
    paths_between_opposite_corners_optimization_0(grid, count, fill, n, x-1, y);
    paths_between_opposite_corners_optimization_0(grid, count, fill, n, x, y+1);
    paths_between_opposite_corners_optimization_0(grid, count, fill, n, x, y-1);
    grid[x][y] = 0;
    fill -= 1;
    return *count;
}

// a large optimization can be made upon noticing the fact that if the path cannot continue forward,
// but can only take two opposite paths, then the grid is effectively split into two parts with unvisited squares,
// and filling one part of board will require overlapping to go to the other part,
// hence the algorithm doesn't need to check further since it cannot continue

int paths_between_opposite_corners_optimization_1_grid_split_check(int** grid, int n, int x, int y) {
    int p = 0;
    int q = 0;
    if(x + 1 > n - 1 || grid[x + 1][y]) p++;
    if(x - 1 < 0 || grid[x - 1][y]) p++;
    if(y + 1 > n - 1 || grid[x][y + 1]) q++;
    if(y - 1 < 0 || grid[x][y - 1]) q++;
    if((p == 2 && q == 0) || (p == 0 && q == 2)) return 1;
    return 0;
}

int paths_between_opposite_corners_optimization_1(int** grid, int* count, int fill, int n, int x, int y) {
    if(fill == n * n - 1 && x == n - 1 && y == n - 1) return ++*count;
    if(x == n - 1 && y == n - 1) return *count;
    if(x > n - 1 || y > n - 1) return *count;
    if(x < 0 || y < 0) return *count;
    if(grid[x][y]) return *count;
    if(paths_between_opposite_corners_optimization_1_grid_split_check(grid, n, x, y)) return *count;
    grid[x][y] = 1;
    fill += 1;
    paths_between_opposite_corners_optimization_1(grid, count, fill, n, x + 1, y);
    paths_between_opposite_corners_optimization_1(grid, count, fill, n, x - 1, y);
    paths_between_opposite_corners_optimization_1(grid, count, fill, n, x, y + 1);
    paths_between_opposite_corners_optimization_1(grid, count, fill, n, x, y - 1);
    grid[x][y] = 0;
    fill -= 1;
    return *count;
}

// the time to search can be further halved by considering one starting direction,
// since every other path is basically mirror image across the principal diagonal.

int paths_between_opposite_corners_optimization_2(int** grid, int n, int x, int y) {
    grid[0][0] = 1;
    int count = 0;
    paths_between_opposite_corners_optimization_1(grid, &count, 1, n, 1, 0);
    return 2 * count;
}

int paths_between_opposite_corners_benchmarking(int n) {
    int** grid = malloc(sizeof(int*) * n);
    for(int i = 0; i < n; i++) {
        grid[i] = malloc(sizeof(int) * n);
        memset(grid[i], 0, sizeof(int) * n); 
    }

    int count = 0;

    clock_t begin = clock();
    printf("-----------------\n");
    printf("No Optimization: %d\n", paths_between_opposite_corners_optimization_0(grid, &count, 0, n, 0, 0));
    printf("time taken: %.2f seconds\n", (float)(clock()-begin)/CLOCKS_PER_SEC);
    printf("-----------------\n");
    begin = clock();
    count = 0;
    printf("Optimization 1: %d\n", paths_between_opposite_corners_optimization_1(grid, &count, 0, n, 0, 0));
    printf("time taken: %.2f seconds\n", (float)(clock()-begin)/CLOCKS_PER_SEC);
    printf("-----------------\n");
    begin = clock();
    printf("Optimization 2: %d\n", paths_between_opposite_corners_optimization_2(grid, n, 0, 0));
    printf("time taken: %.2f seconds\n", (float)(clock()-begin)/CLOCKS_PER_SEC);
    printf("-----------------\n");

    for(int i = 0; i < n; i++) {
        free(grid[i]);
    }
    free(grid);
    return 0;
}

int main() {
    paths_between_opposite_corners_benchmarking(7); // 111712
    return 0;
}
