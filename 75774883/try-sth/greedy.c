#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <math.h>

int string_to_int(string input);
void greedy_recur(int remain);

int main(int argc, string argv[])
{
    if(argc != 2)
    {
        printf("Usage: ./greedy [number]\n");
        return 1;
    }

    string input = argv[1];
    int numb = string_to_int(input);
    greedy_recur(numb);


}



int string_to_int(string input)
{
    int output = 0;
    for(int i = 0, n = strlen(input); i < n; i++)
    {
        if (input[i] < 48 || input[i] > 57)
        {
            printf("Invalid input\n");
            return 2;
        }
        output += pow(10,i) * (int) (input[i] - 48);
    }
    return output;
}

void greedy_recur(int remain)
{
    if (remain <= 0)
    {
        return;
    }

     
}