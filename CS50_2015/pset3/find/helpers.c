/**
 * helpers.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Helper functions for Problem Set 3.
 */
       
#include <cs50.h>
#include <stdio.h>

#include "helpers.h"

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
{
    bool x = recursive(0, n-1, value, values);
    if(x == true)
    {
        return true;
    }
    return false;
        
}

/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{
    // TODO: implement an O(n^2) sorting algorithm
    // haystack == values[], size == n                                                          //TODO: MAKE AN IMPLEMENTATION WITH BUBBLESORT, MERGESORT, INSERTION SORT, SELECTION SORT TO EXPERIMENT WITH OPTIMISATION!
    bubble(values, n);
    return;
}

bool iterative(int value, int values[], int n)
{
    int start = 0, end = n-1, midpoint = 0;
    while(start <= end)                                                                         //TODO: MAKE AN IMPLEMENTATION WITH RECURSION INSTEAD O
    {
        midpoint = (start+end)/2;
        if(value > values[midpoint])
        {
            start = midpoint+1;
        }
        else if(value < values[midpoint])
        {
            end = midpoint-1;
        }
        else
        {
            return true;
        }
    }
    return false;
}

bool recursive(int start, int end, int value, int values[])
{
    int midpoint = (start+end)/2;
    if(end < start)
    {
        return false; 
    }
    else if(value > values[midpoint])
    {
        return recursive(midpoint+1, end, value, values); 
    }
    else if(value < values[midpoint])
    {
        return recursive(start, midpoint-1, value, values);
    }
    else
    {
        return true;   
    }
}

void bubble(int values[], int n)
{
    int placeholder = 0, check = 0;
    while(check == 0)
    {
        int steps = 0;
        for(int i = 0; i < (n - 1); i++)
        {
            if(values[i] > values[i+1])
            {
                placeholder = values[i+1];
                values[i+1] = values[i];
                values[i] = placeholder;
                steps++; 
            }
        
        } 
        if(steps == 0)
        {
            check = 1;   
        }
    }    
    for(int i = 0; i < n; i++)
    {
        printf("%d\n", values[i]);   
    }
    return;   
}

void selection(int values[], int n)
{
    int j = 1, minimum = 0, placeholder = 0;
    while(j < n)
    {
        for(int i = j; i < n; i++)
        {
            if(values[i] < values[i-1])
            {
                minimum = values[i];
                placeholder = i;
            }
        }
        values[placeholder] = values[j];
        values[j] = minimum;
        j++;
    }
    
    
    for(int i = 0; i < n; i++)
    {
        printf("%d\n", values[i]);   
    }
    return;
}

void insertion(int values[], int n)
{
    for(int i = 0; i < n; i++)
    {
        
    }
}