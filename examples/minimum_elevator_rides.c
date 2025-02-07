// there is an elevator that can take maximum weight and there are n people with known weights
// the goal is to find the minimum number of rides required to take each of them from one floor to another

// this can be done naively by calculating and checking each permutation of people
// a much more efficient method is by converting permutations into subsets using bitmasking and
// using dynamic programming with bit represented subsets as states

int minimum_elevator_rides(int n, int* weights, int max_weight) {
    int best[1<<n][2];
    best[0][0] = 1;
    best[0][1] = 0;

    for(int s = 1; s < (1<<n); s++) {
        best[s][0] = n + 1;
        best[s][1] = 0;
        for(int p = 0; p < n; p++) {
            if(s & (1<<p)) {
                int option[2];
                option[0] = best[s^(1<<p)][0];
                option[1] = best[s^(1<<p)][1];
                if(option[1] + weights[p] <= max_weight) {
                    option[1] += weights[p];
                } else {
                    option[0] += 1;
                    option[1] = weights[p];
                }
                if(option[0] < best[s][0] || (option[0] == best[s][0] && option[1] <= best[s][1])) {
                    best[s][0] = option[0];
                    best[s][1] = option[1];
                }
            }
        }
    }
    return best[(1<<n) - 1][0];
}

int main() {
    return 0;
}
