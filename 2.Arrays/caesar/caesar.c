#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool only_digits(string x);
char rotate(char c, int n);

int main(int argc, string argv[])
{
    // Confirm argument is valid
    if (argc != 2 || only_digits(argv[1]) == false)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    // Convert key to int and reduce to reasonable size
    int key = atoi(argv[1]) % 26;
    
    // Prompt user for plaintext
    string plaintext = get_string("plaintext: ");
    
    // Print ciphertext
    printf("ciphertext: ");
    for (char *p = plaintext; *p != '\0'; p++)
    {
        printf("%c", rotate(*p, key));
    }
    printf("\n");
}


// Confirm argument is digits
bool only_digits(string s)
{
    for (char *p = s; *p != '\0'; p++)
    {
        if (!isdigit(*p)) return false;
    }
    return true;
}


// Rotate alphabetical characters by KEY spaces
char rotate(char c, int n)
{
    if (!isalpha(c)) return c;
    int base = (isupper(c)) ? 'A' : 'a';
    return ((c - base + n) % 26) + base;
}
