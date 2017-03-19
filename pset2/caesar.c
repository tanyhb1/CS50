#include <stdio.h>
#include <stdlib.h>
#include <cs50.h>
#include <string.h>

int main(int argc, string argv[])
{
    
       if(argc != 2 || argv[1] == NULL)
       {
            printf("Please enter a number for the cipher.\n");
            return 1;
       }
       else
       {
            int k = atoi(argv[1]); 
            printf("Please enter the text that you want to encrypt: ");
            string text = GetString();
            
            for(int i = 0, length = strlen(text); i < length; i++)
            {
                int math = text[i] + (k % 26);                                                  // ciphered text
                if(64 < text[i] && text[i] < 91)                                                //UPPER CASE LETTERS
                {
                    if(math > 90)                                                 //FOR IT TO LOOP AROUND THE END CHAR
                    {                                                                           
                        printf("%c", math % 90 + 64);                         
                    }
                    else
                    {
                        printf("%c", math);   
                    }
                }
                
                else if(96 < text[i] && text [i] < 123)                                         //LOWER CASE LETTERS
                {
                    if(math > 122)                                                  //FOR IT TO LOOP AROUND THE END CHAR
                    {
                        printf("%c", math % 122 + 96);   
                    }
                    else
                    {
                        printf("%c", math);
                    }
                }
                else
                {
                    printf("%c", text[i]);
                }
            }
            printf("\n");
       }
       
       return 0;
}