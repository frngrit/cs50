#include <stdio.h>
#include <cs50.h>


//declare meow first
void meow(int n, string mes); //prototype



int main(void)
{

    meow(3,"hi");


    /*
    for (int j = i; i > 0; i--)
    {
        printf("meow!!\n");
    }
    */
}


//If you define your function after execute it, there will be error
void meow(int n, string mes)
{
    int i = 0;
    while (i < n)
    {
        //print("meow\n"); old version print meow n times
        printf("%s\n",mes); //new version print message from user n times
        i += 1;
    }

}