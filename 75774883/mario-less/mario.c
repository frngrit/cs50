#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int n = 9;
    while (n < 1 || n > 8)
    {
        n = get_int("Height: ");
    }
    //for row
    for (int i = 0; i < n; i++)
    {
        //for space column
        for (int j = 0; j < (n - i - 1); j++)
        {
            printf(" ");
        }
        for (int k = 0; k < (i + 1); k++)
        {
            printf("#");
        }
        printf("\n");
    }
}