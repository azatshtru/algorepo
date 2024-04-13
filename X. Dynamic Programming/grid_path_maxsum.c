//There is a grid with numbers in each cell. Starting from the top-left corner.
//Find the path to reach the bottom-right corner while only moving down or right such that the sum of the cells in the path is maximum.

int gridPathMaxSum(int* A, int n) {
    int sum[n+1][n+1];
    sum[0][0] = A[0];
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            sum[i][j] = (sum[i-1][j] > sum[i][j-1] ? sum[i-1][j] : sum[i][j-1]) + A[i*n+j];
        }
    }
    return A[n*n];
}