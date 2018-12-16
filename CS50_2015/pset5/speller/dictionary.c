/**
 * Implements a dictionary's functionality.
 */

#include <stdbool.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "dictionary.h"

/**
 * Returns true if word is in dictionary else false.
 */
 
typedef struct trie
{
    struct trie *next[28];
    bool check;
    
}trie;

trie *root = NULL;
int dictionaryWords = 0;
void unloadNode(trie *node);

/**
 * Loads dictionary into memory. Returns true if successful else false.
 */
bool load(const char *dictionary)
{

    //opening file
    FILE *input = fopen(dictionary, "r");
    
    //initialising trie data structure
    root = malloc(sizeof(trie));

    if(root == NULL)
    {
        printf("failed to allocate memory to root\n");
        return false;
    }
    //setting pointer to root
    trie *start = root;
    trie *trav = start;
    int key = 0, index = 0;
    
    //loading dictionary into memory
    for(int c = fgetc(input); c != EOF; c = fgetc(input))
    {   
        key = c%97;
        
        if(c == '\'')
        {
            key = 26;
        }
        else if(c == 10)
        {

            key = 27;   
        }
        
        if((*trav).next[key] == NULL)
        {
            (*trav).next[key] = malloc(sizeof(trie));   
        }
        
        trav = (*trav).next[key];
        
        //if char is \0 and char count > 0 we know it is the end of the string, so close off the node.
        if(key == 27 && index > 0)
        {
            (*trav).check = true;
            index = 0;
            trav = start;
            dictionaryWords++;
        }
        
        index++;    
    }
    (*trav).next[27] = malloc(sizeof(trie));  
    trav = (*trav).next[27];
    (*trav).check = true;   
    dictionaryWords++;
    
    
    fclose(input);
    
    return true;
}

bool check(const char *word)
{
    int counter = 0, key = 0;
    trie *checker = root;
    while(word[counter] != '\0')
    {
        if(word[counter] == '\'')
        {
            key = 26;
        }
        else
        {
            key = toupper(word[counter])%65;
        }
        
        
        if((*checker).next[key] == NULL)
        {
            return false;
        }
        else
        {
            checker = (*checker).next[key];
            counter++;
        }
    }
    if((*checker).next[27] == NULL)
    {
        return false;   
    }
    else
    {
        checker = (*checker).next[27];
    }
    if((*checker).check == true)
    {
        return true;
    }
    return false;
}
/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    return dictionaryWords;
    return 0;
}

/**
 * Unloads dictionary from memory. Returns true if successful else false.
 */
bool unload(void)
{
    //PSEUDOCODE:
    //iterate over first node of trie, finding for characters. if characters found, go deeper into the node, checking at each node whether check is true. if true, is word; then check if next node is null. if not null, then carry on iterating deeper until null. once at end, free() the node.
    unloadNode(root);
    return true;
}

void unloadNode(trie *node)
{
    for(int i = 0; i < 28; i++)
    {
        if((*node).next[i] != NULL)
        {
            unloadNode((*node).next[i]);
        }

    }
    free(node);
}