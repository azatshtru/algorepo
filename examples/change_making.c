#include <stdio.h>
#include "../headers/miniqutils.h"

int change_with_minimum_coins(int* coins, int pocketsize, int n) {
    int change[n+1];
    int first[n+1];
    change[0] = 0;
    for(int x = 1; x <= n; x++) {
        change[x] = I32_MAX;
        for(int i = 0; i < pocketsize; i++) {
            int c = coins[i];
            if(x - c >= 0 && change[x - c] + 1 < change[x]) {
                change[x] = change[x - c] + 1;
                first[x] = c;
            }
        }
    }
    printf("[ ");
    while(n > 0) {
        printf("%d, ", first[n]);
        n -= first[n];
    }
    printf("\b\b ]\n");
    return change[n];
}

int total_coin_combinations(int* coins, int pocketsize, int n) {
    int count[n+1];
    count[0] = 1;
    memzero(count, pocketsize);
    for(int x = 0; x <= n; x++) {
        for(int i = 0; i < pocketsize; i++) {
            int c = coins[i];
            if(x - c >= 0) {
                count[i] += count[x - c];
            }
        }
    }
    return count[n];
}

int main() {
    return 0;
}
