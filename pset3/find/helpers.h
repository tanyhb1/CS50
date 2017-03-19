/**
 * helpers.h
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Helper functions for Problem Set 3.
 */
 
#include <cs50.h>

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n);

/**
 * Sorts array of n values.
 */
void sort(int values[], int n);

/**
 * recursive binary search.
 */ 

bool recursive(int start, int end, int value, int values[]);

/**
 *  iterative binary search.
 */
 
bool iterative(int value, int values[], int n);

/**
 *  bubble sort
 */
 
void bubble(int values[], int n);

 /**
*  selection sort
 */
 
void selection(int values[], int n); 

/**
 *  insertion sort
 */

void insertion(int values[], int n);