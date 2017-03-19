/**
 * generate.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Generates pseudorandom numbers in [0,LIMIT), one per line.
 *
 * Usage: generate n [s]
 *
 * where n is number of pseudorandom numbers to print
 * and s is an optional seed
 */
 
#define _XOPEN_SOURCE

#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// constant
#define LIMIT 65536

int main(int argc, string argv[])
{
    // if wrong number of command line arguments given, i.e. number of pseudo-random numbers to be generated and/or seed is not entered, program will return specifications of the command line argument to the user.
    if (argc != 2 && argc != 3)
    {
        printf("Usage: generate n [s]\n");
        return 1;
    }

    // initialising integer n as the command line argument arg[v], remembering that it is a string and that atoi converts it into an integer for usage.
    int n = atoi(argv[1]);

    // if argc == 3, which means that a seed was provided to use in the srand48 function, run srand48 with seed argv[2] in order to create a seed for usage in drand48.
    if (argc == 3)
    {
        srand48((long int) atoi(argv[2]));
    }
    else
    {
        srand48((long int) time(NULL));
    }

    // print out the number of pseudo random number integers equal to user's spec. since drand48 returns numbers from 0.00 to 1, multiply by 65536 to get a 'random' number.
    for (int i = 0; i < n; i++)
    {
        printf("%i\n", (int) (drand48() * LIMIT));
    }

    // success
    return 0;
}