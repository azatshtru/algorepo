#include "../std/string.c"

int min_3(int a, int b, int c) {
    int min = a;
    if(min > b) { min = b; }
    if(min > c) { min = c; }
    return min;
}

int edit_cost(string a, string b, int i, int j) {
    if(a.str[i]==b.str[j]) { return 0; }
    return 1;
}

int edit_distance(string a, string b, int x, int y, int** A) {
    if(x<0 || y<0) { return 0; }
    if(A[y][x] != -1) {
        return A[y][x];
    }
    A[y][x] = min_3(edit_distance(a, b, x-1, y, A)+1, edit_distance(a, b, x, y-1, A)+1, edit_distance(a, b, x-1, y-1, A)+edit_cost(a, b, x, y));
    return A[y][x];
}

int string_editDistance(string a, string b) {
    int x = a.length;
    int y = b.length;
    int** A = (int**)malloc(y * sizeof(int*));
    for(int i = 0; i < y; i++) { *(A+i) = (int*)malloc(sizeof(int)*x); }
    for(int i = 0; i < y; i++) {
        for(int j = 0; j < x; j++) {
            A[i][j] = -1;
        }
    }
    int k = edit_distance(a, b, x-1, y-1, A);
    for(int i = 0; i < y; i++) { free(*(A+i)); }
    free(A);
    return k;
}