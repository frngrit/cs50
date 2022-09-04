#include <cs50.h>
#include <stdio.h>

int main(void)
{
    /*
    int score1 = 72;
    int score2 = 73;
    int score3 = 33;
    */

    int n = get_int("Enter number of grades: ");

    // use array instead
    int scores[n];

    /*
    This is redundant
    scores[0] = 72;
    scores[1] = 73;
    scores[2] = 33;
    */
    int sum = 0;
    // use this
    for (int i = 0; i < n; i++)
    {
        scores[i] = get_int("Enter grade: ");
        sum += scores[i];
    }

    printf("average score is %f\n", sum / (float) n);
}