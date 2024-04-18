#include "../II. Sorting/sorting.c"

//Find if a subarray sums to a number k. Amortized O(n)
int find_subarray_sum(int len, int* A, int k) {
    int p = 0;
    int q = 0;
    int sum = A[0];
    while(q != len-1 || p != len-1) {
        if(sum==k) {
            printf("%d:%d\n", p, q);
            return 1;
        }
        if(sum < k && q+1<len && sum+A[q+1] <= k) { 
            q += 1;
            sum += A[q];
        } else if(q+1<len && sum+A[q+1] > k && p+1 <= q) {
            sum -= A[p];
            p += 1;
        }
    }
    return -1;
}

//Find two numbers in the array such that their sum is k. Amortized O(n)
int two_sum(int len, float* A, int k) {
    //sort the array
    merge_sort(A, -1, len-1);
    int p = 0;
    int q = len-1;
    while(p != q) {
        if((int)(A[p]+A[q]) == k) { printf("\n%d+%d=%d\n", (int)A[p], (int)A[q], (int)(A[p]+A[q])); return 1; }
        if((int)(A[p]+A[q]) < k) { p+=1; }
        else if((int)(A[p]+A[q]) > k) { q-=1; }
    }
    return -1;
}