#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

char replace_vowel(char c);

int main(int argc, string argv[])
{
    // Ensure argument provided
    if (argc != 2)
    {
        printf("Usage: ./no-vowels word\n");
        return 1;
    }

    string word = argv[1];
    // Use pointer to iterate over string
    for (char *p = word; *p != '\0'; p++)
    {
        printf("%c", replace_vowel(*p));
    }
    printf("\n");
}

char replace_vowel(char c)
{
    switch (tolower(c))
    {   
        case 'a': return '6';        
        case 'e': return '3';        
        case 'i': return '1';
        case 'o': return '0';
        default: return c;
    }
}
