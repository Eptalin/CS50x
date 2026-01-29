#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

float calc_letters(string text);
float calc_words(string text);
float calc_sentences(string text);

int main(void)
{
    // Prompt user to input text
    string text = get_string("Text: ");

    // Plug values into the Coleman-Liao Index
    float L = (calc_letters(text) / calc_words(text)) * 100.0;
    float S = (calc_sentences(text) / calc_words(text)) * 100.0;

    float CLI = 0.0588 * L - 0.296 * S - 15.8;
    int grade = round(CLI);

    if (grade < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (grade >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", grade);
    }
}

float calc_letters(string text)
{
    // Calculate the total number of letters in the text
    float letters = 0;

    for (int i = 0, len = strlen(text); i < len; i++)
    {
        if (isupper(text[i]))
        {
            letters++;
        }
        if (islower(text[i]))
        {
            letters++;
        }
    }
    return letters;
}

float calc_words(string text)
{
    // Calculate the total number of words in the text
    float words = 0;

    for (int i = 0, len = strlen(text); i < len; i++)
    {
        if (isspace(text[i]))
        {
            words++;
        }
    }
    return words + 1;
}

float calc_sentences(string text)
{
    // Calculate the total number of words in the text
    float sentences = 0;

    for (int i = 0, len = strlen(text); i < len; i++)
    {
        if (text[i] == '.' || text[i] == '?' || text[i] == '!')
        {
            sentences++;
        }
    }
    return sentences;
}
