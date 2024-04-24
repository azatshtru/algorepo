#include <stdlib.h>
#include "./popcount.c"

//In dynamic programming, if an algorithm requires subsets as states during memoization, ...
//integer represented bit sets can be used to store said subsets.

int min_2(int a, int b) { return a > b ? b : a; }

//`productPriceList` is the 2D array containing product number on the first dimension and their prices over the days on the second dimension.
int minOptimalProductSelection(int** productPriceList, int numProducts, int days) {
    int total[1<<numProducts][days];
    for(int d = 0; d < days; d++) {
        for(int i = 0; i < (1<<numProducts); i++) {
            total[i][d] = 0;
        }
    }
    for(int i = 0; i < numProducts; i++) { total[1<<i][0] = productPriceList[i][0]; }
    for(int d = 1; d < days; d++) {
        for(int s = 0; s < (1<<numProducts); s++) {
            total[s][d] = total[s][d-1];
            for(int i = 0; i < numProducts; i++) {
                if(s&(1<<i)) {
                    if(parallel_popcount(s)==d+1 && total[s][d]==0) {
                        total[s][d] = total[s^(1<<i)][d-1]+productPriceList[i][d];
                    } 
                    total[s][d] = min_2(total[s][d], total[s^(1<<i)][d-1]+productPriceList[i][d]);
                }
            }
        }
    }
    for(int i = 0; i < numProducts; i++) { free(productPriceList[i]); }
    free(productPriceList);
    return total[(1<<numProducts)-1][days-1];
}

int** generateSampleProductPriceList() {
    int list[3][8] = { { 6, 9, 5, 2, 8, 9, 1, 6 }, { 8, 2, 6, 2, 7, 5, 7, 2 }, { 5, 3, 9, 7, 3, 5, 1, 4 } };
    int** productList = (int**)malloc(sizeof(int*)*3);
    for(int i = 0; i < 3; i++) { productList[i] = (int*)malloc(sizeof(int)*8); }
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 8; j++) { productList[i][j] = list[i][j]; }
    }
    return productList;
}