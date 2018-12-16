#include <stdio.h>

int main(void)
{
    int x=0, y=0;
    printf("minutes:");
    scanf("%d", &x);
    while (x < 0)
    {
        printf("minutes:");
        scanf("%d", &x);
    }
    y = x * 12;   
    printf("bottles:%d\n", y);
}