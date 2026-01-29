#include <cs50.h> // -lcs50
#include <ctype.h>
#include <math.h> // -lm
#include <stdio.h>
#include <string.h>

#define GRADE_BUFFER 20

void count_all(string text, float *letters, float *words, float *sentences);
int calc_CLI(float letters, float words, float sentences);
void report_grade(int grade, char result[]);

int main(void)
{
    // Prompt user to input text
    string text = get_string("Text: ");

    // Count letters, words, sentences
    float letters = 0, words = 1, sentences = 0;
    count_all(text, &letters, &words, &sentences);
    
    // Compute rounded Coleman-Liao Index
    int grade = calc_CLI(letters, words, sentences);

    // Print reading level
    char result[GRADE_BUFFER];
    report_grade(grade, result);
    printf("%s", result);
}

void count_all(string text, float *letters, float *words, float *sentences)
{
    for (char *p = text; *p != '\0'; p++)
    {
        if (isalpha(*p))
        {
            (*letters)++;
        }
        else if (isspace(*p))
        {
            (*words)++;
        }
        else if (*p == '.' || *p == '?' || *p == '!')
        {
            (*sentences)++;
        }
    }
}

int calc_CLI(float letters, float words, float sentences)
{
    float L = letters / words * 100.0;
    float S = sentences / words * 100.0;
    float CLI = 0.0588 * L - 0.296 * S - 15.8;
    return round(CLI);
}

void report_grade(int grade, char result[])
{
    if (grade < 1)
    {
        snprintf(result, GRADE_BUFFER, "Before Grade 1\n");
    }
    else if (grade >= 16)
    {
        snprintf(result, GRADE_BUFFER, "Grade 16+\n");
    }
    else
    {
        snprintf(result, GRADE_BUFFER, "Grade %i\n", grade);
    }
}