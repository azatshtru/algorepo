#include "../headers/popcount.h"

/// utilities to find the number of set bits or ones or population count in values

int popcount_naive(int x) {
    int count = 0;
    while(x) { count += x&1; x=x>>1; }
    return count;
}

int popcount_lookup_table(int x) {
    unsigned char BitsSetTable256[256] = {
        #define B2(n) n, n+1, n+1, n+2
        #define B4(n) B2(n), B2(n+1), B2(n+1), B2(n+2)
        #define B6(n) B4(n), B4(n+1), B4(n+1), B4(n+2)
        B6(0), B6(1), B6(1), B6(2) 
    };

    return BitsSetTable256[x & 0xff] 
    + BitsSetTable256[(x>>8) & 0xff]
    + BitsSetTable256[(x>>16) & 0xff]
    + BitsSetTable256[x>>24];
}

int popcount_parallel(int x) {
    x = x - ((x>>1) & 0x55555555); // count set bits for all two bits
    x = (x & 0x33333333) + ((x>>2) & 0x33333333); // add pairs of adjecent two bits
    x = (x & 0x0F0F0F0F) + ((x>>4) & 0x0F0F0F0F); // add pairs of adjacent 4 bits into a byte
    x = x & 0xF0F0F0F; // filter junk values in the first 4 bits of every byte, since 8 bits can contain atmost 8, or b1000 ones 
    return (x*0x01010101)>>24; // add the 4 bytes into the first byte and shifting to return result
}

/// popcount_sparse_ones is used if it is known that ones are relatively less compared to zeroes
int popcount_sparse_ones(int x) { 
    int count = 0;
    while(x) { x &= (x-1); ++count; }
    return count;
}
