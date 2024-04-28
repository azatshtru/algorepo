//All the subsets of the given set are assigned values, the problem is calculate the sum of values of subsets of each subset.

void subset_sum(int n, int* values) {
    int sum[1<<n];
    for(int i = 0; i < 1<<n; i++) { sum[i] = values[i]; }
    for(int i = 0; i < n; i++) {
        for(int s = 0; s < 1<<n; s++) {
            if(s&(1<<i)) { sum[s] += sum[s^(1<<i)]; }
        }
    }

    for(int i = 0; i < 1<<n; i++) {
        printf("%d: %d\n", i, sum[i]);
    }
}