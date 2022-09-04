#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

int main(int argc, string argv[])
{
    //check if user doesn't input the key
    if (argc != 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
    //check if user input negative key
    long key = 0;
    for (int i = 0, n = strlen(argv[1]); i < n; i++)
    {
        if (argv[1][i] < '0' || argv[1][i] > '9')
        {
            printf("Usage: ./caesar key\n");
            return 1;
        }
        //turn user input (string) into integer
        int str_to_number = (int) argv[1][i] - 48;
        key += str_to_number * pow(10, n - i - 1);
    }

    //prompt for user's input
    string plain = get_string("plaintext:  ");

    printf("ciphertext: ");

    int i = 0;
    char c;
    while (plain[i] != '\0')
    {
        c = plain[i];
        //check if c is upper-case and it is alphabet
        if (isupper(c) && isalpha(c))
        {
            c = c - 65 + key; //decrease c to range [0,26]
            c = c % 26; //mod if c is over 26
            c = c + 65; //get it back to ascii table
            //printf("%i\n", c);
        }
        //check if c is lower-case and it is alphabet
        if (islower(c) && isalpha(c))
        {
            c = c - 97 + key; //decrease c to range [0,26]
            c = c % 26; //mod if c is over 26
            c = c + 97; //get it back to ascii table
            //printf("%i\n", c);
        }
        printf("%c", c);
        i++;
    }
    printf("\n");
}