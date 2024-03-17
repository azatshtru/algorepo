#include <stdlib.h>

#define FNV_PRIME 16777619
#define FNV_OFFSET_BASIS 2166136261
#define TABLE_SIZE 100

int fnv1a_hash(int length, char* s) {
    long int hash = FNV_OFFSET_BASIS;
    for(int i = 0; i < length; i++) {
        hash = hash ^ *(s+i);
        hash = hash * FNV_PRIME;
    }
    return hash%TABLE_SIZE;
}