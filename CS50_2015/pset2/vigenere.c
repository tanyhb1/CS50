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
        printf("Please enter the sentence you want to encrypt.\n");
        string s = GetString();                                                 //get string
        int plength = strlen(phrase);                                           //find string to be encrypted length for later
        for(int i = 0; i < plength; i++)                                        // convert string into number from 1-26 to act as cipher
        {
            phrase[i] = toupper(phrase[i]);                                     // make all characters upper case for ease
            if('A'<= phrase[i] && phrase[i] <= 'Z')
            {
                phrase[i] = (phrase[i])%'A';
            }
            else if('0'<=phrase[i] && phrase[i] <= '9')                         // considering numbers as well, alpha numerical. we aint about numbercism
            {
                phrase[i] = (phrase[i])%'0';
            }
            
        }
        int counter = 0;                                                        // to account for special characters like space and fullstop during alignment of cipher to message.
        for(int i = 0, length = strlen(s); i < length; i++)
        {
            int encrypt = (s[i] + phrase[(i-counter)%plength]);                 //(i - counter) == accounting for above; %plength to repeat cipher from start when reach the end.
            
            if('a' <= s[i] && s[i] <= 'z')                                      // lower case 
            {
                if('z' < encrypt)                                               // if the value of encrypt[i] goes above 'z' i wanna loop back to 'a'
                {
                    printf("%c", (encrypt%'z')+'a'-1);                          // always get the off-by-1 error because im dumb af.
                }
                else
                {
                    printf("%c", encrypt);   
                }
            }
            else if('A' <= s[i] && s[i] <= 'Z')                                 // upper case
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
                counter++;                                                      //else, meaning special characters not alphanumeric, will have to account for shift in cipher. thus counter++ to subtract from above.
            }
            
        }
        printf("\n");

    }
    return 0;
}
