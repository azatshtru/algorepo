#include "../I. Arrays, Traversal and Flags/array.c"

//Dynamic Array is built on top of a regular array which is grown and shrunk according to it's contents. 
//The first position stores the regular array, the second position stores the pointer to a float which signifies the fill level of the dynamic array.
float** DynamicArray() {
    float* A = Array(5);
    float* P = (float*)malloc(sizeof(float));
    float** L = (float**)malloc(sizeof(float)*2);
    *P = -1;
    *L = A;
    *(L+1) = P;
    return L;
}

int push(float** A, float x) {
    **(A+1) += 1; 
    float k = **(A+1);
    if(k < len(*A) - 1) {
        set(*A, k, x);
        return 0;
    }
    float* T = Array(2*len(*A));
    for(int i = 0; i < len(*A); i++) { set(T, i, get(*A, i)); }
    set(T, k, x);
    clear(*A);
    *A = T;
    return 0;
}

float pop(float** A, int i) {
    float r = get(*A, i);
    **(A+1) -= 1;
    int k = **(A+1);
    for(int j = i; j < k+1; j++) { set(*A, j, get(*A, j+1)); }
    set(*A, k+1, 0);
    if(k < len(*A)/2 && len(*A)>5) {
        float* T = Array(len(*A)/2);
        for(int j = 0; j < len(T); j++) { set(T, j, get(*A, j)); }
        clear(*A);
        *A = T;
    }
    return r;
}

int insert(float** A, int i, int x) {
    push(A, 0);
    float p = get(*A, i+1);
    float q = get(*A, i);
    for(int j = i; j < **(A+1); j++){ 
        set(*A, j+1, q); 
        q = p;
        p = get(*A, j+2);
    }
    set(*A, i, x);
    return 0;
}

float popinsert(float** A, float i, float x) {
    float r = pop(A, i);
    insert(A, i, x);
    return r;
}

float* ref(float** A) {
    return *A;
}

int clean(float** A) {
    clear(*A);
    free(*(A+1));
    free(A);
    return 0;
}

int print(float** A) {
    int i;
    printf("\n[ ");
    for(i = 0; i < **(A+1); i++) {
        printf("%.2f, ", get(*A, i));
    }
    printf("%.2f ]\n", get(*A, i));
    return 0;
}