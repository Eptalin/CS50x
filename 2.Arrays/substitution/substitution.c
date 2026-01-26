#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool alphabetical(string x);
bool duplicate(string y);

int main(int argc, string argv[])
{
    // Confirm that 1 argument was added
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }

    // Confirm the key is 26 alphabet characters
    else if (strlen(argv[1]) != 26 || alphabetical(argv[1]) == false)
    {
        printf("Key must contain 26 alphabet characters.\n");
        return 1;
    }

    // Confirm there are no duplicate characters in the key
    else if (duplicate(argv[1]) == false)
    {
        printf("Key must not contain duplicate characters.\n");
        return 1;
    }
    // If the key passes all the tests, continue program
    else
    {
        // Convert key into all capitals
        for (int i = 0; i < 26; i++)
        {
            argv[1][i] = toupper(argv[1][i]);
        }

        // Prompt user for plaintext
        string plaintext = get_string("plaintext: ");

        // Print the ciphertext by substituting characters
        char ciphertext = 0;
        printf("ciphertext: ");
        for (int i = 0, len = strlen(plaintext); i < len; i++)
        {
            if (isupper(plaintext[i]))
            {
                ciphertext = argv[1][plaintext[i] - 65];
                printf("%c", ciphertext);
            }
            else if (islower(plaintext[i]))
            {
                ciphertext = (argv[1][plaintext[i] - 97]) + 32;
                printf("%c", ciphertext);
            }
            else
            {
                printf("%c", plaintext[i]);
            }
        }
        printf("\n");
    }
}

bool alphabetical(string x)
{
    // Check that all characters in the key are alphabet
    for (int i = 0, len = strlen(x); i < len; i++)
    {
        if (isalpha(x[i]))
        {
        }
        else
        {
            return false;
        }
    }
    return true;
}

bool duplicate(string y)
{
    // Create array to count frequency of letters and initialise all to 0
    int letters[26];
    for (int i = 0; i < 26; i++)
    {
        letters[i] = 0;
    }

    // Scan the key and tally up how often each letter appears
    for (int j = 0, len = strlen(y); j < len; j++)
    {
        if (isupper(y[j]))
        {
            letters[y[j] - 'A']++;
        }
        else if (islower(y[j]))
        {
            letters[y[j] - 'a']++;
        }
    }
    // If there are no duplicate characters, return True
    for (int k = 0; k < 26; k++)
    {
        if (letters[k] > 1)
        {
            return false;
        }
    }
    return true;
}
