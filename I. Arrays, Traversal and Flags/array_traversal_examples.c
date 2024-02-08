//Along with the array come two fundamental techniques that are used almost everytime in writing larger algorithms.

#include <stdio.h>
#include "array.c"

//Traversal is a standard algorithm on an array which passes through each element of the array once, allowing analysis of each element.
//A loop can be used to traverse through an array using its API.
//Additionally, a flag can be used to keep track of properties of the entire array that are derived through individual analysis of elements.

//Following function traverses through an array and prints all the numbers that are between zero and one.
//This is an example of conditional traversal.
int nums_bw01(float* A) {
    for(int i = 0; i < len(A); i++) {
        if(get(A, i)>0 && get(A, i)<1) {
            printf("%.2f\n", get(A, i));
        }
    }
    return 0;
}


//Following function takes in an Array and a number. 
//It traverses through the array and using a flag, keeps count of the occurences of the given number. 
//This is an example of traversal using flags.
int count(float* A, float x) {
    int count = 0; //This is a flag.
    for(int i = 0; i < len(A); i++) {
        if(get(A, i) == x) {
            count++;
        }
    }
    return count;
}

//Flags keep track of some overall information about the array, like the occurrence of a particular element...
//...said information is obtained by analyzing each element through traversal.