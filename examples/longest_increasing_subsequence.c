#include "../headers/vector.h"

int binary_search_int(int* array, int len, int x) {
    int l = 0;
    int r = len - 1;

    while(l <= r) {
        int m = (l + r)/2;
        if(array[m] < x) {
            l = m + 1; 
        } else if(array[m] > x) {
            r = m - 1;
        } else {
            return m;
        }
    }

    return len;
}

int longest_increasing_subsequence(int* array, int len) {
    vector(int) subsequence = vec_new(int);

    for(int i = 0; i < len; i++) {
        int x = array[i];
        int cutoff = binary_search_int(vec_as_array(subsequence), vec_len(array), x);
        
        if(cutoff == vec_len(subsequence)) {
            vec_push(subsequence, x);
        } else {
            vec_set(subsequence, cutoff, x);
        }
    }
    return vec_len(subsequence);
}

int main() {
    return 0;
}
