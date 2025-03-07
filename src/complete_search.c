#include "../headers/complete_search.h"
#include "../headers/logging.h"

int subset_next(vector(int) subset, int n) {
    int len = vec_len(subset);
    if(len == 0) {
        vec_push(subset, 0);
        return 0;
    }
    int last = vec_get(subset, len - 1);
    if(last == n) {
        if(len == 1) return 0;
        vec_pop(subset, -1);
        int x = vec_pop(subset, -1);
        vec_push(subset, x + 1);
        return 0;
    }
    vec_push(subset, last + 1);
    return 0;
}

int permutation_next(int* permutation, int n) {
    int len = n + 1;
    int visited[len];
    memzero(visited, sizeof(int) * len);

    while(permutation[n] < permutation[n - 1]) {
        visited[permutation[n--]] = 1;
    }
    visited[permutation[n--]] = 1;
    int x = permutation[n];

    for(int i = x; i < len; i++) {
        if(!visited[i]) continue;
        permutation[n++] = i;
        visited[x] = 1;
        visited[i] = 0;
        break;
    }

    for(int i = 0; i < len; i++) {
        if(!visited[i]) continue;
        permutation[n++] = i;
    }
    return 0;
}
