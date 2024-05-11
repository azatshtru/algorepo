#include <stdlib.h>
#include <string.h>

#ifndef STRING
#define STRING

typedef unsigned char uint8;
typedef signed char int8;
typedef char byte;

typedef struct _string {
    uint8 len;
    char str[];
} string;

typedef char* String;

char* string_new() {
    string* s = (string*)malloc(sizeof(string));
    s->len = 0;
    return s->str;
}

char* string_from(char* str_literal) {
    uint8 len = strlen(str_literal);
    string* s = (string*)malloc(sizeof(string)+len);
    s->len = len;
    memcpy(s->str, str_literal, len);
    return s->str;
}

string* string_address(char* str) { return (string*)(str-(uintptr_t)(&((string*)0)->str)); }

uint8 string_len(char* str) { return string_address(str)->len; }

void string_free(char* str) { free(string_address(str)); }

void string_push(char** old_str, char* push_str) {
    uint8 old_len = string_len(*old_str);
    uint8 push_str_len = strlen(push_str);
    string* s = (string*)malloc(sizeof(string)+old_len+push_str_len);
    s->len = old_len+push_str_len;
    memcpy(s->str, *old_str, old_len);
    memcpy(s->str+old_len, push_str, push_str_len);
    string_free(*old_str);
    *old_str = s->str;
}

void string_print(char* str) {
    uint8 len = string_address(str)->len;
    printf("str! \"");
    for(int i = 0; i < len; i++) { printf("%c", str[i]); }
    printf("\"\n");
}

int8 string_compare(char* s1, char* s2) {
    uint8 len = string_len(s1) < string_len(s2) ? string_len(s1) : string_len(s2);
    int i = 0;
    while(i < len && s1[i] == s2[i]) { i++; }
    if(i==len && len == string_len(s2)) { return 0; }
    return s1[i] < s2[i] ? -1 : 1;
}

#endif