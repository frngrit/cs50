#include <stdio.h>
#include <cs50.h>

int main(void){
    long x = get_int("x : ");
    long y = get_int("y : ");

    string ans = "x is equal to y";
    if (y > x){
        ans = "y is greater than x";
    }
    else if (y < x){
        ans = "x is greater than y";
    }
    printf("%s\n",ans);
}