#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

// Allocate points to each letter of the alphabet
int points[26] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

int calculate(string word);

int main(void)
{
    // Prompt Player 1 and Player 2 to enter their words
    string word1 = get_string("Player 1: ");
    string word2 = get_string("Player 2: ");

    // Calculate scores
    int score1 = calculate(word1);
    int score2 = calculate(word2);

    // Print results
    if (score1 > score2)
    {
        printf("Player 1 wins!\n");
    }
    else if (score1 < score2)
    {
        printf("Player 2 wins!\n");
    }
    else if (score1 == score2)
    {
        printf("Tie!\n");
    }
}

int calculate(string word)
{
    int score = 0;

    for (int i = 0, len = strlen(word); i < len; i++)
    {
        if (isupper(word[i]))
        {
            score += points[word[i] - 'A'];
        }
        if (islower(word[i]))
        {
            score += points[word[i] - 'a'];
        }
    }
    return score;
}
