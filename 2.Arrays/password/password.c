// Check that a password has at least one lowercase letter, uppercase letter, number and symbol
// Practice iterating through a string
// Practice using the ctype library

#include <cs50.h>
#include <ctype.h>
#include <stdio.h>

bool valid(string password);

int main(void)
{
    string password = get_string("Enter your password: ");
    if (valid(password))
    {
        printf("Your password is valid!\n");
    }
    else
    {
        printf("Your password needs at least one uppercase letter, lowercase letter, number and symbol\n");
    }
}

// Validate password
bool valid(string password)
{
    bool lower = false, upper = false, number = false, symbol = false;
    for (char *p = password; *p != '\0'; p++)
    {
        if (islower(*p)) lower = true;
        if (isupper(*p)) upper = true;
        if (isdigit(*p)) number = true;
        if (ispunct(*p)) symbol = true;
    }
    return lower && upper & number && symbol;
}
