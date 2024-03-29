#include <stdio.h>

//Von-Neumann architecture divides computers into three parts: CPU, Memory and I/O.
//The CPU uses memory to perform operations using electrical signals.
//Memory is stored in stacks and heaps. The stack fills up during normal code flow, and heap memory needs to be allocated manually.
//When a function is run, the function call is pushed onto the stack and when the function returns, the function call is popped off.

//Recursion happens when a function calls itself. Many algorithmic problems can be solved intuitively when using recursion.
//Everytime recursion happens, function calls start stacking up, a base case is required to stop recursion and to pop function calls off the stack.

//This code demonstrates recursion by two examples: calculating nth fibonacci series element, calculating the factorial of a number.

int fib(int n) {
    if(n==0 || n==1) { return 1; }
    return fib(n-1) + fib(n-2);
}

int factorial(int n) {
    if(n==0) { return 1; }
    return n*factorial(n-1);
}