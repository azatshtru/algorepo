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
    KeyValuePair** table;
} Hashmap;

Hashmap* createHashmap() {
    Hashmap* A = (Hashmap*)malloc(sizeof(Hashmap));
    A->table = (KeyValuePair**)malloc(sizeof(KeyValuePair*)*TABLE_SIZE);
    for(int i = 0; i < TABLE_SIZE; i++) { *(A->table+i) = NULL; }
    return A;
}

KeyValuePair* entry(Hashmap* map, char* key) {
    KeyValuePair* kv = *(map->table + fnv1a_hash(key));
    while(kv != NULL && !streql(kv->key, key)) { kv = kv->next; }
    return kv;
}

int insert(Hashmap* map, char* key, float value) {
    if(entry(map, key) == NULL) {
        KeyValuePair* kv = (KeyValuePair*)malloc(sizeof(KeyValuePair));
        kv->key = key;
        kv->value = value;
        kv->next = *(map->table + fnv1a_hash(key));
        *(map->table + fnv1a_hash(key)) = kv;
    } else {
        entry(map, key)->value = value;
    }
    return 0;
}

float discard(Hashmap* map, char* key) {
    KeyValuePair* kv = *(map->table + fnv1a_hash(key));
    if(kv==NULL) {
        return -1;
    } else if(streql(kv->key, key)) { 
        float v = kv->value;
        free(kv);
        return v;
    }
    while(kv->next != NULL && !streql(kv->next->key, key)) { kv=kv->next; }
    if(kv->next != NULL) {
        KeyValuePair* kvx = kv->next;
        kv->next = kv->next->next;
        float v = kvx->value;
        free(kvx);
        return v;
    } 
    return -1;
}