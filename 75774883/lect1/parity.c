#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int n = get_int("n: ");

    if (n%2 == 0)// If n is even
    {
        printf("even\n");
    }
    if (n%2 != 0)
    {
        printf("odd\n");
    }
}