#include <stdlib.h>

typedef struct length_string {
    char* str;
    int length;
} string;

string string_new() {
    string s;
    s.str=NULL;
    s.length = 0;
    return s;
}

string string_from(char* c_arr) {
    string s;
    int len = 0;
    while(c_arr[len] != '\0') { ++len; }
    s.str = (char*)malloc(sizeof(char)*len);
    s.length = len;
    for(int i = 0; i < len; i++) { s.str[i]=c_arr[i]; }
    return s;
}

//consumes both strings and returns a concatenated string.
string string_concat(string a, string b) {
    char str[a.length+b.length];
    int i = 0;
    while(i<a.length) { str[i]=a.str[i]; }
    while(i<a.length+b.length) { str[i] = b.str[i-a.length]; }
    free(a.str);
    free(b.str);
    string s;
    s.length = a.length+b.length;
    s.str = str;
    return s;
}