#include <stdio.h>
#include <stdlib.h>
#include "../headers/miniqutils.h"

unsigned long counting_tilings(int n, int m) {
    if(n > m) {
        n = n ^ m;
        m = n ^ m;
        n = n ^ m;
    }

    unsigned long*** states = malloc(sizeof(unsigned long**)*(m+1));
    for(int i = 0; i < m+1; i++) {
        states[i] = malloc(sizeof(unsigned long*) * (n+1));
        for(int j = 0; j < n+1; j++) {
            states[i][j] = malloc(sizeof(unsigned long) * (1<<n));
            memset(states[i][j], 0, sizeof(unsigned long) * (1<<n));
        }
    }
    
    states[0][n][0] = 1;
 
    for(int i = 1; i <= m; i++){
        for(int mask = 0; mask < (1<<n); mask++)
            states[i][0][mask] = states[i-1][n][mask];
 
        for(int j = 1; j <= n; j++){
            for(int mask = 0; mask < (1<<n); mask++){
 
                int use = (1<<(j-1)) & mask;
 
                if(use){
                    states[i][j][mask]+=states[i][j-1][mask-(1<<(j-1))];
                } else {
                    states[i][j][mask]+=states[i][j-1][mask+(1<<(j-1))];
                    if(j > 1 && !((1<<(j-2)) & mask)) 
                        states[i][j][mask]+=states[i][j-2][mask];
                }
 
                states[i][j][mask] %= 1000000007;
 
            }
        }
    }

    int result = states[m][n][0];

    for(int i = 0; i < m+1; i++) {
        for(int j = 0; j < n+1; j++) {
            free(states[i][j]);
        }
        free(states[i]);
    }
    free(states);

 
    return result;
}

// there is also a direct formula for calculating tilings which works in O(nm).
// $$\prod_{a=1}^{n/2}\prod_{b=1}^{m/2}4(cos^2\frac{\pi a}{n+1}+cos^2\frac{\pi b}{m+1})$$

#include "../tests/orange_juice.h"

oj_test(counting_tilings_returns_2_for_2x2_grid) {
    int result = counting_tilings(2, 2);
    oj_assert_eq_int(2, result);
    oj_fresh;
}

oj_test(counting_tilings_returns_781_for_4x7_grid) {
    int result = counting_tilings(4, 7);
    oj_assert_eq_int(781, result);
    oj_fresh;
}

oj_test(counting_tilings_returns_789797918_for_10x1000_grid) {
    oj_assert_eq_int(789797918, counting_tilings(10, 1000));
    oj_fresh;
}

// run only if you have some time to kill
oj_test(counting_tilings_for_various_grids) {
    oj_assert_eq_int(281, counting_tilings(6, 4));
    oj_assert_eq_int(217283915, counting_tilings(7, 50));
    oj_assert_eq_int(391705009, counting_tilings(8, 123));
    oj_assert_eq_int(0, counting_tilings(9, 999));
    oj_assert_eq_int(296820210, counting_tilings(9, 1000));
    oj_assert_eq_int(449662393, counting_tilings(10, 500));
    oj_assert_eq_int(709630856, counting_tilings(10, 999));
    oj_fresh;
}

oj_prepare(test_counting_tilings) {
    oj_run(counting_tilings_returns_2_for_2x2_grid);
    oj_run(counting_tilings_returns_781_for_4x7_grid);
    oj_run(counting_tilings_for_various_grids);
    oj_report;
    oj_fresh;
}

int main() {
    oj_blend(test_counting_tilings, 0);
    return 0;
}
