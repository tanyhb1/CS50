#include <stdio.h>
#include <stdlib.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

int main(int argc, string argv[])
{
    if(argc == 2)
    {
        string s = argv[1];
        for(int i = 0, length = strlen(s); i < length; i++)
        {
            s[i] = toupper(s[i]);
            printf("%c", s[i]);
        }
    }
    else
    {
     return 1;
    }
    return 0;
}