#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

int main(void)
{
    string s = get_string("s: ");
    printf("\n");

    char t[strlen(s) + 1];



    for (int i = 0, n = strlen(s); i < n; i++)
    {
        t[i] = s[i];
    }

    t[strlen(s)] = '\0';

    if (strlen(t) > 0)
    {
        t[0] = toupper(t[0]);
    }

    printf("s: %s @%p\n", s, s);
    printf("t: %s @%p\n", t, t);

}