int min_coins(int* c, int len_c, int k, int printSolution) {
    int mem[k+1];
    int first[k+1];
    mem[0] = 0;
    for(int i = 1; i < k+1; i++) {
        int min = -1;
        int min_c = 0;
        for(int j = 0; j < len_c; j++) {
            int p = i-c[j];
            if(p<0) { continue; }
            if(min==-1||mem[p]<min){
                min = mem[p];
                min_c = c[j];
            }
        }
        mem[i]=1+min;
        first[i] = min_c;
    }
    if(printSolution) {
        int p = k;
        while(mem[p] > 0) {
            printf("%d ", first[p]);
            p -= first[p];
        }
        printf("\n");
    }
    return mem[k];
}

//To solve dynamic programming problems, think about the recursive approach combined with memoization, then build the solution iteratively.

int total_coin_combos(int* c, int len_c, int k) {
    int mem[k+1];
    for(int i = 0; i < k+1; i++) { mem[i] = 0; }
    mem[0] = 1;
    for(int i = 1; i < k+1; i++) {
        for(int j = 0; j < len_c; j++) {
            int p = i-c[j];
            if(p<0) { continue; }
            mem[i]+=mem[p];
        }
    }
    return mem[k];
}
