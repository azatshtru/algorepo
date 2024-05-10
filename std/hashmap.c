#include <stdlib.h>

#ifndef HASHMAP
#define HASHMAP

typedef unsigned char uint8;
typedef signed char int8;
typedef char byte;

typedef struct key_value_pair {
    byte* key;
    byte* value;
    struct key_value_pair* next;
} KeyValuePair;

typedef struct hashmap {

} HashMap;

#endif