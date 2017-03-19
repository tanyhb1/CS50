#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>


int main(void)
{
    //a proper demonstration of how to copy a string s to a string t, considering that a string is a pointer to a single char, together with proper memory allocation.
    char *s = get_string();
    if(s == NULL)
    {
        return 1;   
    }
    
    char *t = malloc((strlen(s)+1) * sizeof(char));
    if(t == NULL)
    {
        return 1;   
    }
    
    for(int i = 0; i < strlen(s); i++)
    {
        t[i] = s[i];   
    }
    
    if(strlen(t) > 0)
    {
        t[0] = toupper(t[0]);   
    }
    
    printf("string s is: %s\n", s);
    printf("string t is: %s\n", t);
    
    //if we had simply just set t to s, both of them would be the same pointer to the same address of memory, and would be identical (a change to s or t would affect the other). 
    t = s;
    
    t[0] = toupper(t[0]);
    printf("string s is: %s\n", s);
    printf("string t is: %s\n", t);
}