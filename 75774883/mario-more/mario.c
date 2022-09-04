#include <cs50.h>
#include <stdio.h>

int main(void)
{
    //initial value of n to get into input loop
    int n = 9;
    while (n < 1 || n > 8)
    {
        n = get_int("Height: ");
    }

    //draw for row
    for (int i = 0; i < n; i++)
    {
        //print space before brick
        for (int space = 0; space < (n - i - 1); space++)
        {
            printf(" ");
        }
        //print brick after space'
        for (int first = 0; first < (i + 1); first++)
        {
            printf("#");
        }
        //print spaces between brick
        printf("  ");
        //print brick after middle spaces
        for (int last = 0; last < (i + 1); last++)
        {
            printf("#");
        }
        //print new row
        printf("\n");
    }


}
