#include <stdio.h>

void swap(int *a, int *b);

int main(void)
{
    int x = 1, y = 2;
    printf("x is %d, y is %d\n", x, y);
    printf("Swapping...\n");
    swap(&x, &y);                                                       //&x means the address of x, much like int *x. however, x was already declared as an int and thus we use the & identifier to refer to it as a pointer.
    printf("x is %d, y is %d\n", x, y);
}
void swap(int *a, int *b)                                               //int *a is a pointer to the address of a.
{                                                                       //however, when below *a is mentioned, it means instead to go to the address of a and get the value stored there, much like &x
    int temp = *a;
    *a = *b;
    *b = temp;
}
//int *a, *a, &a
//int *a is the same as &a in that both of them refer to the pointers (or address) and not what the pointer is pointing to. *a refers to what the pointer is pointing to. use int *a and &a interchangably, depending on whether
//the variable has already been declared or not.