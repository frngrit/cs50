#include <stdio.h>
#include <cs50.h>
int main(void){
    string answer = get_string("What is your name?\n");
    string bye = "bye";
    printf("hello, %s!!\n%s\n",answer,bye);
}