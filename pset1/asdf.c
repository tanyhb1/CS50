#include <stdio.h>
#include <math.h>

int main(void)
{
    printf(" ");
    printf("#");
    float f = 4.23;
    int c = roundf(f*100);
    printf("%d", c);
}