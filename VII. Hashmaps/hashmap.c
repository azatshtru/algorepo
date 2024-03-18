#include <stdlib.h>

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

typedef struct hashmap {
    KeyValuePair* table;
} Hashmap;

Hashmap* createHashmap() {
    Hashmap* A = (Hashmap*)malloc(sizeof(Hashmap));
    A->table = (KeyValuePair*)malloc(sizeof(KeyValuePair)*TABLE_SIZE);
    for(int i = 0; i < TABLE_SIZE; i++) { 
        (A->table+i)->next = NULL; 
        (A->table+i)->key = "";
        (A->table+i)->value = 0;
    }
    return A;
}

KeyValuePair* entry(Hashmap* A, char* key) {
    KeyValuePair* kvi = A->table + fnv1a_hash(key);
    while(kvi->next != NULL && !streql(kvi->key, key)) { kvi = kvi->next; }
    return kvi;
}

float get(Hashmap* A, char* key) {
    if(streql(entry(A, key)->key, key)) { return entry(A, key)->value; }
    return -1;
}

int insert(Hashmap* A, char* key, float value) {
    KeyValuePair* kv = (KeyValuePair*)malloc(sizeof(KeyValuePair));
    kv->key = key;
    kv->value = value;
    kv->next = NULL;
    if(!len((A->table+fnv1a_hash(key))->key)) {
        *(A->table + fnv1a_hash(key)) = *kv; 
        free(kv);
    } else if(streql(entry(A, key)->key, key)){
        entry(A, key)->value = value; 
        free(kv);
    } else {
        entry(A, key)->next = kv;
    }
    return 0;
}