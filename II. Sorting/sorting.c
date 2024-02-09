#include "../I. Arrays, Traversal and Flags/array_traversal.c"
#include <time.h>

int sorted(float* A) {
    int flag = 1;
    for(int i = 1; i < len(A); i++) {
        if(get(A, i)<get(A, i-1)){
            flag = 0;
        }
    }
    return flag;
}

int shuffle(float* A) {
    srand(time(0));
    for(int i = 0; i < len(A); i++) {
        int r = (float)rand()/RAND_MAX * len(A);
        float k = get(A, r);
        set(A, r, get(A, i));
        set(A, i, k);
    }
}

// O(n^2) sorting algorithm
int bubble_sort(float* A) {
    int i;
    int j;
    for(i = 0; i < len(A); i++) {
        for(j = 0; j < len(A)-i-1; j++) {
            if(get(A, j+1)<get(A, j)) {
                float k = get(A, j+1);
                set(A, j+1, get(A, j));
                set(A, j, k);
            }
        }
    }
    return 0;
}

//Inversion refers to the number of pairs of elements in the array that are in the wrong order.
//Swapping the elements of inversion reduces the number of inversions by 1.

int merge(float* A, int a, int c, int b) {
    float* T = Array(b-a);
    int p = a;
    int q = c;
    int i = 0;
    while(p < c && q < b) {
        get(A, p) < get(A, q) ? set(T, i, get(A, p++)) : set(T, i, get(A, q++));
        i++;
    }
    int r = p >= c ? q : p;
    for(int j = i; j < len(T); j++) { set(T, j, get(A, r++)); }
    for(i = a; i < b; i++){ set(A, i, get(T, i-a)); }
    clear(T);
    return 0;
}

// O(nlogn) sorting algorithm
int merge_sort(float* A, int a, int b) {
    if(b - a == 1) {
        return 0;
    }
    int c = (a+b)/2;
    merge_sort(A, a, c);
    merge_sort(A, c, b);
    merge(A, a, c, b);
    return 0;
}

// O(n) sorting algorithm. This variation works only with a small set of positive integers.
int counting_sort(float* A) {
    int n = array_max(A);
    float* A1 = Array(n+1);
    for(int i = 0; i < len(A); i++) {
        set(A1, (int)get(A, i), get(A1, get(A, i))+1);
    }
    int j = 0;
    for(int i = 0; i <= n; i++) {
        while(get(A1, i) > 0.1) { 
            set(A1, i, get(A1, i)-1);
            set(A, j++, i); 
        }
    }
    clear(A1);
    return 0;
}

// O(n!) sorting algorithm.
int bogosort(float* A) {
    while(sorted(A) != 1) {
        shuffle(A);
        prettyPrint(A);
    }
    return 0;
}