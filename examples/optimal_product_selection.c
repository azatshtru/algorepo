#include <stdlib.h>
#include "../headers/popcount.h"
#include "../headers/miniqutils.h"

/// a state of dynamic programming that holds subsets or permutations can be represented using bitmasking

// `productPriceList` is the 2D array containing product number in the first dimension and
// their prices over the days in the second dimension

int minOptimalProductSelection(int** productPriceList, int numProducts, int days) {
    int total[1<<numProducts][days];
    memzero(total, (1<<numProducts) * days);
    for(int i = 0; i < numProducts; i++) {
        total[1<<i][0] = productPriceList[i][0];
    }
    for(int day = 1; day < days; day++) {
        for(int s = 0; s < (1<<numProducts); s++) {
            total[s][day] = total[s][day - 1];
            for(int i = 0; i < numProducts; i++) {
                if(s & (1<<i)) {
                    if(popcount_parallel(s) == day + 1 && total[s][day] == 0) {
                        total[s][day] = total[s ^ (1<<i)][day - 1]+productPriceList[i][day];
                    } 
                    total[s][day] = min_i(2, total[s][day], total[s ^ (1<<i)][day - 1] + productPriceList[i][day]);
                }
            }
        }
    }
    return total[(1<<numProducts)-1][days-1];
}

#include "../tests/orange_juice.h"

oj_test(testMinOptimalProductSelection) {
    int** productList = malloc(sizeof(int*) * 3);
    int product1[8] = { 6, 9, 5, 2, 8, 9, 1, 6 };
    int product2[8] = { 8, 2, 6, 2, 7, 5, 7, 2 };
    int product3[8] = { 5, 3, 9, 7, 3, 5, 1, 4 };
    productList[0] = product1;
    productList[1] = product2;
    productList[2] = product3;
    int result = minOptimalProductSelection(productList, 3, 8);
    free(productList);

    oj_assert_eq_int(5, result);
    oj_fresh;
}

oj_prepare(testMinOptimalProductSelectionSuite) {
    oj_run(testMinOptimalProductSelection);
    oj_report;
    oj_fresh;
}

int main() {
    oj_blend(testMinOptimalProductSelectionSuite, 0);
    return 0;
}
