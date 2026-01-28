#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool only_digits(string x);
char rotate(char c, int n);

int main(int argc, string argv[])
{
    if (argc != 2 || only_digits(argv[1]) == false)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
    else
    {
        int key = atoi(argv[1]);
        string plaintext = get_string("plaintext: ");

        printf("ciphertext: ");
        for (int i = 0, len = strlen(plaintext); i < len; i++)
        {
            printf("%c", rotate(plaintext[i], key));
        }
        printf("\n");
    }
}

bool only_digits(string x)
{
    // Check that there are only digits in the argument
    for (int i = 0, len = strlen(x); i < len; i++)
    {
        if (isdigit(x[i]))
        {
        }
        else
        {
            return false;
        }
    }
    return true;
}

char rotate(char c, int n)
{
    // Rotate the characters in the plaintext by KEY spaces
    char x = 0;
    if (isupper(c))
    {
        x = (((c - 65) + n) % 26) + 65;
    }
    else if (islower(c))
    {
        x = (((c - 97) + n) % 26) + 97;
    }
    else
    {
        x = c;
    }
    return x;
}
