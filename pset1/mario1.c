#include <stdio.h>

int main(void)
{
    int height=0, counter=0;
    do
    {
        printf("height:");
        scanf("%d", &height);
    }
    while(height<0 || height>23);  
    
    for(int i=0; i<height; i++)
    {
        for(int j=0; j<height; j++)
        {
            if(j<=height-2-counter)
            {
                printf(" ");
            }
            else
            {
                printf("#");
            }
            
        }
        printf("\n");
        counter=counter+1;
    }
}