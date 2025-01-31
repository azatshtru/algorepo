#include "../headers/miniqutils.h"

int knapsack_01(int* weights, int weights_len, int capacity) {
    int knapsack[weights_len][capacity + 1];
    memzero(knapsack, sizeof(int)*weights_len*(capacity + 1));
    knapsack[0][0] = 1;
    for (int k = 1; k <= capacity; k++) {
        for (int x = 0; x <= weights_len; x++) {
            if (x - weights[k] >= 0) knapsack[x][k] |= knapsack[x - weights[k]][k-1];
            knapsack[x][k] |= knapsack[x][k-1];
        }
    }
    return knapsack[weights_len - 1][capacity];
}

int knapsack_01x(int* weights, int weights_len, int capacity) {
    int knapsack[capacity + 1];
    memzero(knapsack, sizeof(int)*(capacity + 1));
    knapsack[0] = 1;
    for (int k = 1; k <= capacity; k++) {
        for (int x = weights_len; x >= 0; x--) {
            if (knapsack[x]) {
                knapsack[x + weights[k]] = 1;
            }
        }
    }
    return knapsack[capacity];
}

int main() {
    return 0;
}
