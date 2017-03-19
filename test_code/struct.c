#include <stdio.h>
#include <stdlib.h>



int main(void)
{
    int *x = malloc(sizeof(int));
    for(int i = 0; i < 10; i++)
    {
        x[i] = i;
        printf("%d", x[i]);
    }
    
}
