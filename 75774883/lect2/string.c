#include <stdio.h>
#include <cs50.h>
#include <string.h>

int main(void)
{
    string s = get_string("Input:  ");
    printf("Output: ");

    // for (int i = 0; i < strlen(s); i++)
    // {
    //     printf("%c",s[i]);
    // }
    // slow becuase you have to recheck the condition which run strlen again and again

    // for (int i =0, n = strlen(s); i < n; i++)
    // {
    //     printf("%c",s[i]);
    // }

    // int i =0;
    // while (s[i] != '\0')
    // {
    //     printf("%c",s[i]);
    //     i++;
    // }

    for (int i = 0; s[i] != '\0'; i++)
    {
        printf("%c",s[i]);
    }

    printf("\n");
}