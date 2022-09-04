#include <stdio.h>
#include <cs50.h>


void recursion(int n);

int main(void)
{
    int n = get_int("Enter number: ");

    recursion(n);
}


void recursion(int n)
{
    if (n <= 0)
    {
        return;
    }

    recursion(n-1);

    printf("%i\n", n);
}