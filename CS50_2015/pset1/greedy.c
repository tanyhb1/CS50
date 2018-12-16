#include <stdio.h>
#include <cs50.h>
#include<math.h>

int main(void)
{
    float c = 0;
    int change = 0, counter = 0;
    
    
    do
    {
        printf("How much change is owed, sir?\n");
        c = GetFloat();
    }
    while(c < 0);
    
    change = roundf(c * 100);       // in cents instead of dollars.
    
    while(change >= 25)
    {
        change = change - 25;
        counter++;
    }
    while(change >= 10)
    {
        change = change - 10;
        counter++;
    }
    while(change >= 5)
    {
        change = change - 5;
        counter++;
    }
    while(change >=1)
    {
        change = change -1;   
        counter++;
    }
    printf("%d\n", counter);
}