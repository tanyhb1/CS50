#include <stdio.h>
#include <cs50.h>

//recursive collatz
int collatz(int number, int *steps);


int main(void)
{
    printf("Please enter the integer that you want to test the collatz function on: \n");
    int n = get_int();
    int steps = 0;
    collatz(n, &steps);
    printf("Steps taken: %d\n", steps);
}

int collatz(int number, int *steps)
{
    if(number == 1)
    {
        return *steps;
    }
    else if(number%2 == 0)
    {
        *steps = *steps + 1;
        return collatz(number/2, steps);
    }
    else if(number%2 == 1)
    {
        *steps = *steps + 1;
        return collatz((3*number)+1, steps);
    }
    return 1;
}