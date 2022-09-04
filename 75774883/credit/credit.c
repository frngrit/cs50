#include <cs50.h>
#include <stdio.h>
#include <math.h>
//AMX 15-digit, start with 34-37
//MTC 16-digit, start with 51, 52, 53, 54, 55
//VIS 13-16 digit start with 4


long floorDivision(long numb, long divisor);

int main(void)
{

    //Get user's number
    long numb = get_long("Number: ");
    //Check if it's not 13-16 digit
    int digit_13 = floorDivision(numb, 1E12); //If number is below 13-digit, value has to be 0
    int digit_16 = floorDivision(numb, 1E15); //If number is above 16-digit, value has to be more than 9
    if (digit_13 == 0 || digit_16 > 9)
    {
        printf("INVALID\n");
        return 0;
    }


    //check if it valid
    long dup_numb = numb;
    int i = 1;//define counter
    int sum = 0; //define sum of checksum
    int last_digit = 0;
    while (dup_numb != 0)
    {

        //get last digit by mod 10
        last_digit = dup_numb % 10;

        //check if it's even digit (not multipy by 2)
        if (i % 2 != 0)
        {
            sum += last_digit;
        }
        else
        {
            last_digit = 2 * last_digit;
            //if multipled number has 2-digit
            if (last_digit > 9)
            {
                sum += last_digit % 10; //plus last digit
                sum += floorDivision(last_digit, 10); //plus first digit
            }
            else
            {
                sum += last_digit;
            }
        }
        //printf("%li and %i and %i\n",numb,sum,last_digit);
        //get rid of last digit
        dup_numb = floorDivision(dup_numb, 10);
        i += 1;
    }

    //checksum
    if (sum % 10 != 0)
    {
        printf("INVALID\n");
        return 0;
    }

    //get first two digit of card no.
    long first_two = floorDivision(numb, pow(10, i - 3));
    long first = floorDivision(first_two, 10); //get first digit of card number
    long last = first_two % 10; //get second digit of card number

    //printf("%i, %li, %li, %i\n",i-1,first,last,sum);
    //Check if it AMEX
    if (first == 3 && (last == 4 || last == 7) && i - 1 == 15)
    {
        printf("AMEX\n");
    }
    else if (first == 5 && last >= 1 && last <= 5 && i - 1 == 16)
    {
        printf("MASTERCARD\n");
    }
    else if (first == 4 && i - 1 >= 13 && i - 1 <= 16)
    {
        printf("VISA\n");
    }
    else
    {
        printf("INVALID\n");
    }

}

long floorDivision(long numb,  long divisor)
{
    double res = numb % divisor;
    double cleaned = numb - res;
    double floor_div = cleaned / divisor;
    return floor_div;
}