/// there is a grid with numbers in each cell.
/// starting from the top-left corner, find the path to reach the bottom-right corner 
/// while only moving down or right such that the sum of the cells in the path is maximum.

int grid_path_max_sum(int* grid, int n) {
    int sum[n+1][n+1];
    sum[0][0] = grid[0];
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            sum[i][j] = (
                sum[i-1][j] > sum[i][j-1]
                ? sum[i-1][j] 
                : sum[i][j-1]
            ) + grid[i*n+j];
        }
    }
    return grid[n*n];
}

int main() {
    return 0;
}
