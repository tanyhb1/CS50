#include <stdio.h>
#include <cs50.h>

int collatz(int n);

int main(void)
{
    printf("Please enter the integer that you want to test the collatz function on: \n");
    int n = get_int();
    printf("Steps taken: %d\n",  collatz(n));
}

int collatz(int n)
{
    if(n == 1)
    return 0;
    else if(n%2 == 0)
    return 1+collatz(n/2);
    else if(n%2 == 1)
    return 1+collatz(3*n+1);
    return 1;
}