#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

// Allocate points to each letter of the alphabet
int points[26] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

int calculate(string word);
string report_winner(int score1, int score2);

int main(void)
{
    // Prompt Player 1 and Player 2 to enter their words
    string word1 = get_string("Player 1: ");
    string word2 = get_string("Player 2: ");

    // Calculate scores
    int score1 = calculate(word1);
    int score2 = calculate(word2);

    // Print results
    printf("%s", report_winner(score1, score2));
}

int calculate(string word)
{
    int score = 0;
    for (char *p = word; *p != '\0'; p++)
    {
        score += (isalpha(*p)) ? points[tolower(*p) - 'a'] : 0;
    }
    return score;
}

string report_winner(int score1, int score2)
{
    if (score1 > score2)
    {
        return "Player 1 wins!\n";
    }
    else if (score1 < score2)
    {
        return "Player 2 wins!\n";
    }
    else
    {
        return "Tie!\n";
    }
}
