#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // Prompt user for card number
    long card_number;
    do
    {
        card_number = get_long("Card Number: ");
    }
    while (card_number < 1);

    // Save 2 copies of the card number to use in later calculations
    long i = card_number;
    long j = card_number;

    // Separate out individual digits and add them
    int sum_digits = 0;
    do
    {
        // Add digits up
        sum_digits += card_number % 10;
        card_number /= 10;

        // Multiply every 2nd digit by 2 and add it
        int n = card_number % 10 * 2;
        if (n > 9)
        {
            n -= 9;
        }
        sum_digits += n;
        card_number /= 10;
    }
    while (card_number > 0);

    // Report results
    if (sum_digits % 10 == 0)
    {
        int length;
        for (length = 0; i > 0; length++)
        {
            i /= 10;
        }

        do
        {
            j /= 10;
        }
        while (j > 100);

        if (length == 13 || length == 16)
        {
            if (length == 16 && j > 50 && j < 56)
            {
                printf("MASTERCARD\n");
            }
            else if (j > 39 && j < 50)
            {
                printf("VISA\n");
            }
            else
            {
                printf("INVALID\n");
            }
        }
        else if (length == 15)
        {
            if (j == 34 || j == 37)
            {
                printf("AMEX\n");
            }
            else
            {
                printf("INVALID\n");
            }
        }
        else
        {
            printf("INVALID\n");
        }
    }
    else
    {
        printf("INVALID\n");
    }
}
