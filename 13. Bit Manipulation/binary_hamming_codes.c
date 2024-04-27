#include "popcount.c"
//given two bit strings, find how often they differ

int hamming(int a, int b) { return parallel_popcount(a^b); }