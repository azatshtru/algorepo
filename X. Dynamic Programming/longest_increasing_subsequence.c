#include <math.h>

//O(n^2)
int longest_increasing_subsequence_nsq(int* A, int len) {
    int mem[len];
    for(int i = 0; i < len; i++) { mem[i] = 1; }
    for(int i = 1; i < len; i++) {
        for(int j = 0; j < i; j++) {
            if(A[j]<A[i]) {
                mem[i] = mem[j]+1 > mem[i] ? mem[j]+1 : mem[i];
            }
        }
    }
    int max = mem[len];
    for(int i = 1; i < len; i++) { max = max < mem[i] ? mem[i] : max; }
    return max;
}

//O(nlogn)
int longest_increasing_subsequence(int* A, int len) {
    int L = 0;
    int mem[len];
    int aux[len+1];
    for(int i = 0; i < len; i++) { mem[i] = 1; }
    for(int i = 0; i < len+1; i++) { aux[i] = -INFINITY; }

    for(int i = 0; i < len; i++) {
        if(aux[L] < A[i]) {
            L += 1;
            aux[L] = A[i];
        }
        int b = 0;
        for(int k = L/2; k > 0; k/=2) {
            while(k+b < L && aux[k+b] <= A[i]) { b+=k; }
        } 
        if(b+1 < L+1){ aux[b+1] = A[i]; }
    }
    return L;
}