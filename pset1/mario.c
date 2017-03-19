#include <stdio.h>

int main(void)
{
    int height = 0, counter = 0, width = 0;
    while(height <= 0 || height > 23 )
    {
        printf("height:");
        scanf("%d", &height);
    }
    width = height+1;
    while(counter < height-1)              //height of the pyramid
    {
        int counter2 = 0;
        int x = width-counter;
        while(counter2 < width)             //width of the pyramid
        {
            if (counter2 < x-2)
            {
                printf(" ");
            }
            else if(counter2 >= x-2) 
            {
                if(counter2 == width-1)
                {
                    printf("#\n");
                }
                else
                {
                    printf("#");
                }
                
            }
            counter2 = counter2+1;
        }
        counter = counter+1;
    }
} 