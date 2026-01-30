#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool validate_args(int argc, string key);
bool alphabetical(string s);
bool duplicate(string s);
char cipher(char c, string key);

int main(int argc, string argv[])
{
    // Validate arguments
    string key = argv[1];
    if (!validate_args(argc, key)) return 1;

    // Convert key into all capitals
    for (int i = 0; i < 26; i++)
    {
        key[i] = toupper(key[i]);
    }

    // Prompt user for plaintext
    string plaintext = get_string("plaintext: ");

    // Print ciphertext
    printf("ciphertext: ");
    for (char *p = plaintext; *p != '\0'; p++)
    {
        printf("%c", cipher(*p, key));
    }
    printf("\n");
}


bool validate_args(int argc, string key)
{
    // Confirm that 1 argument was added
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 0;
    }

    // Confirm key is 26 alphabet characters
    else if (strlen(key) != 26 || alphabetical(key) == false)
    {
        printf("Key must contain 26 alphabet characters.\n");
        return 0;
    }

    // Confirm no duplicate characters in the key
    else if (duplicate(key) == false)
    {
        printf("Key must not contain duplicate characters.\n");
        return 0;
    }
    return 1;
}


// Check all characters in key are alphabetical
bool alphabetical(string s)
{
    for (char *p = s; *p != '\0'; p++)
    {
        if (!isalpha(*p)) return false;
    }
    return true;
}


// Scan key and verify no duplicates
bool duplicate(string s)
{
    int letters[26] = {0};
    for (char *p = s; *p != '\0'; p++)
    {
        if (++letters[toupper(*p) - 'A'] != 1) return false;
    }
    return true;
}


// Substitute the plaintext char using key
char cipher(char plaintext, string key)
{
    if (!isalpha(plaintext)) return plaintext;
    char mapped = key[toupper(plaintext) - 'A'];
    return (isupper(plaintext)) ? mapped : tolower(mapped);
}