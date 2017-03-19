#include <stdio.h>
#include <cs50.h>
typedef struct node
{
    int n;
    struct node *left;
    struct node *right;
}node;

bool search(int n, node *tree)
{
    if(tree == NULL)
    {
        return false;   
    }
    if((*tree).n >n)
    {
        return search(n, (*tree).right);   
    }
    else if((*tree).n < n)
    {
        return search(n, (*tree).left);
    }
    else
    {
        return true;
    }
    return false;
}

int main(void)
{
    bool search(   
}