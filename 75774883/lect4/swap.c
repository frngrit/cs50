#include <stdio.h>

void swap(int *a, int *b);

int main(void)
{
    int x = 1, y = 2;

    printf("before x: %i, y: %i\n", x, y);
    swap(&x, &y);
    printf("after  x: %i, y: %i\n", x, y);
}

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}