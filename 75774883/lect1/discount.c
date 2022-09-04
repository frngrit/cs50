#include <cs50.h>
#include <stdio.h>

float discount(float reg_price, int pct_off);


int main(void)
{
    float regular = get_float("Regular price: ");
    int pct_off = get_int("Percent off: ");
    float discounted = discount(regular,pct_off);
    //float sale = regular * 0.85;

    printf("Sale Price: %.2f\n",discounted);
}

float discount(float reg_price, int pct_off)
{
    return reg_price * (100 - pct_off)/100;
}