#include <stdlib.h>
#include "../V. Sets, Iterators and Options/option.c"

#define FNV_PRIME 16777619
#define FNV_OFFSET_BASIS 2166136261
#define TABLE_SIZE 10

int len(char* s) {
    int count = 0;
    while(*(s++) != '\0') { count+=1; }
    return count;
}

int streql(char* s1, char* s2) {
    if(len(s1) != len(s2)) { return 0; }
    while(*s1 != '\0') {
        if(*(s1++) != *(s2++)) { return 0; }
    }
    return 1;
}

int fnv1a_hash(char* s) {
    unsigned long int hash = FNV_OFFSET_BASIS;
    int length = len(s);
    for(int i = 0; i < length; i++) {
        hash = hash ^ *(s+i);
        hash = hash * FNV_PRIME;
    }
    return hash%TABLE_SIZE;
}

typedef struct kvnode {
    char* key;
    float value;
    struct kvnode* next;
} KeyValuePair;

Option(KeyValuePair);

typedef struct hashmap {
    Option_KeyValuePair* table;
    int* tableCount;
} Hashmap;

Hashmap* createHashmap() {
    Hashmap* A = (Hashmap*)malloc(sizeof(Hashmap));
    A->table = (Option_KeyValuePair*)malloc(sizeof(Option_KeyValuePair)*TABLE_SIZE);
    A->tableCount = (int*)malloc(sizeof(int)*TABLE_SIZE);
    for(int i = 0; i < TABLE_SIZE; i++) { *(A->table+i) = None(); }
    return A;
}

Option_KeyValuePair entry(Hashmap* A, char* key) {
    Option_KeyValuePair o = *(A->table + fnv1a_hash(key));
    if(o.none) { return None(); }
    KeyValuePair* kv = o.some;
    for(int i = 0; i < *(A->tableCount+fnv1a_hash(key)); i++) { 
        if(streql(kv->key, key)) { break; }
        kv = kv->next;
    }
    if(!streql(kv->key, key)) { return None(); }
    return Some(kv);
}

float get(Hashmap* A, char* key) {
    return entry(A, key).none ? -1 : entry(A, key).some->value;
}

int insert(Hashmap* A, char* key, float value) {
    Option_KeyValuePair* o = A->table+fnv1a_hash(key);
    KeyValuePair* kv = (KeyValuePair*)malloc(sizeof(KeyValuePair));
    kv->key = key;
    kv->value = value;
    if(o->none) {
        *o = Some(kv);
        *(A->tableCount + fnv1a_hash(key)) = 0;
    } else if(entry(A, key).none) {
        kv->next = o->some;
        o->some = kv;
        *(A->tableCount + fnv1a_hash(key)) += 1;
    } else {
        entry(A, key).some->value = value;
        free(kv);
    }
    return 0;
}

int discard(Hashmap* A, char* key) {
    Option_KeyValuePair* o = A->table+fnv1a_hash(key);
    if(*(A->tableCount + fnv1a_hash(key)) == 0) {
        
    }

    return 0;
}