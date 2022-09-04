#include <stdio.h>

int main(void)
{
    char *s = "Hi!";
    int i = 0;
    while (*(s+i) != '\0')
    {
        printf("%c\n", *(s+i));
        i++;
    }
}