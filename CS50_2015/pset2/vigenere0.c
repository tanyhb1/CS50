#include <stdio.h>
#include <stdlib.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

int main(int argc, string argv[])
{
    string phrase = argv[1];
    if(argc != 2)
    {
        printf("Please enter a phrase for the cipher.\n");
        return 1;   
    }
    else
    {
       // printf("Please enter the sentence you want to encrypt.\n");
        string s = GetString();
        int plength = strlen(phrase);
        for(int i = 0; i < plength; i++)
        {
            
            phrase[i] = toupper(phrase[i]);   
            phrase[i] = (phrase[i])%'A';
            
        }
        int counter = 0;
        for(int i = 0, length = strlen(s); i < length; i++)
        {
            int encrypt = (s[i] + phrase[(i-counter)%plength]);
            
            if('a' <= s[i] && s[i] <= 'z')
            {
                if('z' < encrypt)
                {
                    printf("%c", (encrypt%'z')+'a'-1);
                }
                else
                {
                    printf("%c", encrypt);   
                }
            }
            else if('A' <= s[i] && s[i] <= 'Z')
            {
                if('Z' < encrypt)
                {
                    printf("%c", (encrypt%'Z')+'A'-1);
                }
                else
                {
                    printf("%c", encrypt);
                }
            }
            else
            {
                printf("%c", s[i]);
                counter++;
            }
            
        }
        printf("\n");

    }
    return 0;
}
