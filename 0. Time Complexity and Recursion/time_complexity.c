#include <stdio.h>

//Every computation takes, be it miniscule, a finite amount of time.
//Time complexity of an algorithm refers to the dependence of time taken to run the algorithm on the input size.

//Time complexity is measured in big O.
//If the time taken scales linearly with the input size, we say the complexity is O(n).
//If the time taken stays relatively the same while running the algorithm regardless of input size, we say its constant time or O(1).
//Other common complexities are O(log n), O(nlog n), O(n^2), O(n^3), O(2^n), O(n!), O((n+1)!)

//This code demonstrates time complexity by performing the sum of first 'n' natural numbers via O(n) algorithm and O(1) algorithm.

//O(n)
unsigned long long int sum_n(unsigned long long int n) {
    unsigned long long int sum = 0;
    for(unsigned long long int i = 1; i <= n; i++) { sum+=i; }
    return sum;
}

//O(1)
unsigned long int sum_1(unsigned long int n) {
    return n*(n+1)/2;
}