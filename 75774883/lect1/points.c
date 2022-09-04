#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int points = get_int("How many points did you lose? ");
    //You should assign your lost cause if you want to change it later, it would be easier
    const int MINE = 2; //You should CAPITALIZED with constant


    if (points > MINE)
    {
        printf("You lost more than me\n");
    }
    else if (points < MINE)
    {
        printf("I lost more than you\n");
    }
    else
    {
        printf("We lost equally\n");
    }
}