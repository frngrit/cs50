#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

char encrypt(char c, string key);

int main(int argc, string argv[])
{
    string alpha = "ABCDEFGHIJKLMNOP";
    const string KEY = argv[1];
    if (argc != 2)
    {
        //hadle when user input incorrectly
        printf("Usage: ./substitution key\n");
        return 1;
    }
    if (strlen(KEY) != 26)
    {
        //handle when user input string length not 26 chars
        printf("Key must contain 26 characters.\n");
        return 1;
    }
    for (int i = 0, n = strlen(KEY); i < n; i++)
    {
        //check if there is any non-alphabet
        if (!isalpha(KEY[i]))
        {
            printf("Invalid characters in key.\n");
            return 1;
        }
        //check the character next to 
        for (int j = i + 1; j < n; j++)
        {
            //check if character duplicate
            if (KEY[i] == KEY[j])
            {
                printf("Duplicate character in key.\n");
                return 1;
            }
        }
    }


    string s = get_string("plaintext:  "); //prompt user for plain text

    printf("ciphertext: ");

    for (int i = 0, n = strlen(s); i < n; i++)
    {
        //encrypt each character
        char c = encrypt(s[i], KEY);
        //print each charater
        printf("%c", c);
    }
    printf("\n");


}


char encrypt(char c, string key)
{
    int index;
    if (c >= 'a' && c <= 'z')
    {
        return tolower(key[c - 97]);
    }
    if (c >= 'A' && c <= 'Z')
    {
        return toupper(key[c - 65]);
    }
    return c;

}