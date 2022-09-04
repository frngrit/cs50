#include <stdio.h>
#include <cs50.h>
#include <ctype.h>

int main(void)
{
    int player1 = get_int("Enter player1's attack damage: ");
    int player2 = get_int("Enter player2's attack damage: ");
    string answer = player1 > player2 ? "Player1 wins\n" : player2 > player1 ? "Player2 wins\n" : "Tie\n";

    printf("%s\n", answer);
}