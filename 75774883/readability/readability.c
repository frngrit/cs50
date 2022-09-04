#include <cs50.h>
#include <stdio.h>
#include <math.h>
#include <ctype.h>
int main(void)
{
    //prompt for user's string
    string s = get_string("Text: ");
    //count for letter
    int i = 0, letters = 0, sentences = 0, words = 1;
    while (s[i] != '\0')
    {

        if (isalpha(s[i]))
        {
            //increment in letter
            letters += 1;
        }
        if (s[i] == ' ')
        {
            //increment in word
            words += 1;
        }
        if (s[i] == '.' || s[i] == '?' || s[i] == '!')
        {
            //increment in sentence
            sentences += 1;
        }
        i++;
    }
    float index = 0.0588 * letters / words * 100 - 0.296 * sentences / words * 100 - 15.8;
    //printf("%i %i %i %f", letters, sentences, words, index);

    //check if index more than or equal 16
    if (index >= 16)
    {
        printf("Grade 16+\n");
    }
    //check if index less than or equal 1
    else if (index <= 1)
    {
        printf("Before Grade 1\n");
    }
    else
    {
        printf("Grade %i\n", (int) round(index));
    }
}