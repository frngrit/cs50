#include <stdio.h>

int main(void)
{
    int numbers[] = {6,7,5,0,3,4};

    for (int i = 0; i < 7; i++)
    {
        if (numbers[i] == -1)
        {
            printf("Found it\n");
            return 0;
        }
    }
    printf("Not Found!\n");
    return 1;
}