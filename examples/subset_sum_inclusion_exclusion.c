// all the subsets of the given set are assigned some values
// the problem is to calculate, for each subset S, the sum of values of subsets of S

void subset_sum_inclusion_exclusion(int n, int* values, int* subset_sums) {
    int sum[1<<n];
    for(int i = 0; i < 1<<n; i++) {
        sum[i] = values[i];
    }
    for(int i = 0; i < n; i++) {
        for(int s = 0; s < 1<<n; s++) {
            if(s & (1<<i)) {
                sum[s] += sum[s ^ (1<<i)];
            }
        }
    }

    for(int i = 0; i < 1<<n; i++) {
        subset_sums[i] = sum[i];
    }
}

int main() {
    return 0;
}
