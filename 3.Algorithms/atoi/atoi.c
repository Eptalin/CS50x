#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int convert(string input);

int main(void)
{
    string input = get_string("Enter a positive integer: ");

    for (int i = 0, n = strlen(input); i < n; i++)
    {
        if (!isdigit(input[i]))
        {
            printf("Invalid Input!\n");
            return 1;
        }
    }

    // Convert string to int
    printf("%i\n", convert(input));
}

int convert(string input)
{
    int n = 0;
    int null_index = strlen(input); 
    if (input[0] != '\0')
    {
        n = input[null_index - 1] - 48;
        input[null_index - 1] = '\0';
        n += convert(input) * 10;
    }
    return n;
}