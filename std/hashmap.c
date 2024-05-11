#include <stdlib.h>

#ifndef HASHMAP
#define HASHMAP

#define FNV_PRIME 16777619
#define FNV_OFFSET_BASIS 2166136261

typedef unsigned char uint8;
typedef signed char int8;
typedef char byte;

typedef struct key_value_pair {
    byte* key;
    byte* value;
    struct key_value_pair* next;
} KeyValuePair;

typedef struct hashmap {
    unsigned int cardinality;
    KeyValuePair* entries[];
} HashMap;

unsigned int hash_fnv1a(char* s, uint8 len, unsigned int cardinality) {
    unsigned long int hash = FNV_OFFSET_BASIS;
    for(int i = 0; i < len; i++) {
        hash = hash ^ *(s+i);
        hash = hash * FNV_PRIME;
    }
    return hash%cardinality;
}

HashMap* hashmap_new() {
    HashMap* hashmap = (HashMap*)malloc(sizeof(HashMap)+sizeof(KeyValuePair*));
    hashmap->cardinality = 1;
    return hashmap;
}

void entry(HashMap* hashmap, char* key) {

}

#endif