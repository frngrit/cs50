#include <stdio.h>

typedef struct
{
    int x;
    int y;
}
corres;

int main(void)
{
    corres array[6];

    int n = 0;
    for (int i = 0; i < 3; i++)
    {

        for (int j = 0; j < 2; j++)
        {
            array[n].x = i;
            array[n].y = j;
            printf("(%i, %i)\n", array[n].x, array[n].y);
            printf("(%p, %p)\n", &(array[n].x), &(array[n].y));

            printf("(%p, %p)\n", &(j), &(j));
        }
        n++;
    }
}