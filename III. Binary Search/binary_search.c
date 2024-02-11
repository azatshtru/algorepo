#include "../II. Sorting/sorting.c"

//The standard way to search for an element in an array is through traversing through the array until you find the given value.
//This is called linear search and takes O(n) time.
//Function returns -1 if the value is not found.
int linear_search(float* A, float x) {
    for(int i = 0; i < len(A); i++) {
        if(get(A, i) == x) {
            return i;
        }
    }
    return -1;
}

//The time taken for search is vastly reduced if the given array is sorted.
//Binary search takes O(log n) to search for a given element in a sorted array.
int binary_search_r(float* A, float x) {
    int a = 0;
    int b;
    for(b = len(A)/2; b >= 1; b /= 2) {
        while(get(A, a+b) <= x && a+b < len(A)) { a += b; }
    }
    if(get(A, a) == x) { return a; }
    return -1;
}

int binary_search_l(float* A, float x) {
    int b = len(A)-1;
    int a;
    for(a = len(A)/2; a >= 1; a /= 2) {
        while(get(A, b-a) >= x && b-a >= 0) { b -= a; }
    }
    if(get(A, b) == x) { return b; }
    return -1;
}