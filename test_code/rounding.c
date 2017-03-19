#include <stdio.h>
#include <cs50.h>
#include <math.h>

float w;
float v;
int intlen(float start);
float rounding(int n);

int main(void)
{
    printf("Please enter a float.\n");
    w = GetFloat();
    printf("To what decimal places do you want your float, sir?\n");
    int n = GetInt();
    v = rounding(n);
    printf("%f\n", v);
    
    
}

float rounding(int n)
{ 
    v = roundf(w*(10^n))/(10^n);
    return v;
}

