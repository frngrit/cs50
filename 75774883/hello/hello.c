#include <stdio.h>
#include <cs50.h>


int main(void)
{
    //get name from user
    string name = get_string("what's your name? ");
    //print hello and user's name
    printf("hello, %s\n", name);
}
