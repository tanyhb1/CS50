#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
//string initials[];

int main(void)
{
    string s = GetString();
    for(int i = 0, n = strlen(s); i < n; i++)
    {
        printf("%c", s[i]+2);   
    }
    printf("\n");
}