#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

int main(void)
{
    string s = GetString();
    for(int i = 0, length = strlen(s); i < length; i++)
    {
        if(i == 0)
        {
            printf("%c", toupper(s[0]));
        }
        else if(s[i] == ' ')
        {
            printf("%c", toupper(s[i+1]));
        }

    }
    printf("\n");
}