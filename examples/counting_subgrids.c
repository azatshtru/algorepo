#include "../headers/popcount.h"

// in a given grid with white and black squares, find all the subgrids where the corners are black squares.
// this can be solved easily if each row is represented as a binary number, then rows are anded.

int counting_subgrids(int n, int* grid) {
    int count = 0;
    for(int i = 0; i < n; i++) {
        for(int j = i + 1; j < n; j++) {
            int k = popcount_parallel(grid[i] & grid[j]);
            if(k > 1) {
                count += k-1;
            }
        }
    }
    return count;
}

int main() {
    return 0;
}
