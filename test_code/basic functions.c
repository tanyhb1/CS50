#include <stdio.h>
#include <cs50.h>

void cough(int n);
int main(void)
{
    int c;
    printf("how many times do you want me to cough, sir?\n");
    c = GetInt();
    cough(c);
}

void cough(n)
{
    for(int i = 0; i < n; i++)
    {
        printf("cough\n");   
    }
}