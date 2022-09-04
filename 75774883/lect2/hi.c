#include <stdio.h>
#include <cs50.h>

int main(void)
{
    // char c1 = 'H';
    // char c2 = 'I';
    // char c3 = '!';

    // string c = "HI!";

    char c[3];
    c[0] = 'H';
    c[1] = 'I';
    c[2] = '!';

    string s = "HI!";

    printf("%i %i %i \n",c[0],c[1],c[2]);
    printf("%i %i %i %i\n",s[0], s[1], s[2], s[3]);
    printf("%s %s \n", c, s);
}
