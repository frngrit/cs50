#include <stdio.h>

int main(void)
{
    int array[] = {1,2,8,4,6,5};

    int max, max_index;
    for (int i = 0; i < 5; i++)
    {
        max = 0;
        for (int j = i; j < 6; j++)
        {
            if (array[j] > max)
            {
                max = array[j];
                max_index = j;
            }
        }
        array[max_index] = array[i];
        array[i] = max;
    }
    for (int i = 0; i < 6; i++)
    {
        printf("%i\n",array[i]);
    }

}
