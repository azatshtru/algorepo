//A set of objects is given.
//The goal is to find the subsets that exhibit certain property.
//For each element, find the possible solutions until the element including and not including said element.
//The union of the solutions (including and non-including) is the result for that element.

//This problem takes in a given set of weights and an integer x, and determines if it is possible to sum to k using the weights.
int weight_sum_knapsack(int weightLength, int* W, int x) {
    int P[weightLength][x+1];
    for(int i = 0; i < weightLength; i++) { P[i][0] = 1; }
    for(int i = 0; i < x+1; i++) {
        for(int w = 0; w < weightLength; w++) {
            if(i-W[w] == 0) { P[w][i]=1; continue; }
            P[w][i] = P[w-1][i-W[w]] || P[w-1][i];
        }
    }
    return P[weightLength-1][x];
}

//Another approach for the knapsack would be to construct the solution through a one dimensional array.
//This solution is based on the fact that when coming from right to left if a solution exists for a value, the solution also exists for a weight added to that value.
//Using this approach the 2D array is reduced down to a 1D array for efficient memory management.

int weight_sum_knapsack1(int weightLength, int* W, int x) {
    int P[x+1];
    P[0] = 1;
    for(int i = 1; i < x+1; i++) { P[i] = 0; }
    for(int w = 0; w < weightLength; w++) {
        for(int i = x; i >= 0; i--) {
            if(P[i]) {
                if(i+W[w]>=x+1) { continue; }
                P[i+W[w]]=1;
            }
        }
    }
    return P[x];
}