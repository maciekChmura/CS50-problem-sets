/**
 * helpers.c
 *
 * Helper functions for Problem Set 3.
 */
 
#include <cs50.h>
#include <math.h>
#include "helpers.h"


/**
 * Returns true if value is in array of n values, else false.
 */
 
 bool searchRecursive(int value, int values[], int start, int end) {
     int middle = ((end - start) / 2) + start;
     
    if (values[middle] == value) {
        //eprintf("found\n");
        return true;
    } else if (start >= end) {
      return false; 
    
    } else if (value < values[middle]) {
        
        // eprintf("start:  %i\n", start);
        // eprintf("middle: %i\n", middle);
        // eprintf("end: %i\n", end);
        // eprintf("left\n");
        
        return searchRecursive( value, values, start, middle - 1);
    } else if (value > values[middle]){
        
        // eprintf("start:  %i\n", start);
        // eprintf("middle: %i\n", middle);
        // eprintf("end: %i\n", end);
        // eprintf("right\n");
        
        return searchRecursive( value, values, middle + 1, end);
     
    } 
    //eprintf("exit\n");
    return false;
}
 
 
 
bool search(int value, int values[], int n)
{
    // TODO: implement a searching algorithm
    if (n < 0) {
        return false;
    }
//     for (int i = 0; i < n; i++) {
//         if ( values[i] == value) {
//             return true;
//         } else {
//             return false;
//         }
//     }
//     return false;
// }
    if ( n > 0 ) {
       return searchRecursive( value, values, 0, n);
    }
    return false;
}

/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{
    // TODO: implement a sorting algorithm
    
    
    int swapCounter = -1;
    //iterate over list
    while (swapCounter != 0) {
    swapCounter = 0;    
    
        for (int i = 0; i < n - 1; i++) {
            
            //compare adjacent elements
            if (values[i] > values[i + 1]) {
                //swap elements that are in the wrong order
                //largest element will bubble to the end
                int helper = values[i + 1];
                values[i + 1] = values[i];
                values[i] = helper;
                swapCounter = 1;
            }
        
        }
    }
    //the list is sorted once no elements have been swaped
    return;
}
