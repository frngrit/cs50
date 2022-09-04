#include <stdio.h>
#include <cs50.h>

int main(void){
    int counter = 1, i = 0;
    int max = get_int("Enter integer number:\n");
    while (counter <= max){
        while (i < counter)
        {
            printf("*");
            i += 1;
        }
        printf("\n");
        i = 0;
        counter += 1;
    }
}

