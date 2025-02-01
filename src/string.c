#include "../headers/string.h"

int cstr_edit_distance(int len_a, char* a, int len_b, char* b) {
    int m = len_a;
    int n = len_b;
    int edit_distance[m+1][n+1];

    for(int i = 0; i <= m; i++) {
        edit_distance[i][0] = i;
    }
    for(int j = 0; j <= n; j++) {
        edit_distance[0][j] = j;
    }

    for(int i = 1; i <= m; i++) {
        for(int j = 1; j <= n; j++) {
            if(a[i - 1] == b[j - 1]) {
                edit_distance[i][j] = edit_distance[i - 1][j - 1];
                continue;
            }
            edit_distance[i][j] = 1 + min_f(3,
                                            edit_distance[i - 1][j],
                                            edit_distance[i][j - 1],
                                            edit_distance[i - 1][j - 1]
                                            );
        }
    }
    return edit_distance[m][n];
}
