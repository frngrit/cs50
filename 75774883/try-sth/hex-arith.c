#include <stdio.h>

int main(void)
{
    int x = 0xa;
    int y = 0xb;

    int answer = x + y;

    printf("%x\n", answer);
    if (0x0e > 0x0a)
    {
        printf("true\n");
    }
}
