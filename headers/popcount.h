#ifndef POPCOUNT
#define POPCOUNT

/// utilities to find the number of set bits or ones or population count in values

int popcount_naive(int x);

int popcount_lookup_table(int x);

int popcount_parallel(int x);

/// popcount_sparse_ones is used if it is known that ones are relatively less compared to zeroes
int popcount_sparse_ones(int x);

/// given two values, find how often their bits differ
int popcount_hamming_distance(int a, int b);

#endif
