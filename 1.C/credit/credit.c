#include <cs50.h>
#include <stdio.h>

bool check_luhn(long card);
void report_type(bool luhn, long card);

int main(void)
{
    // Prompt user for card number
    long card;
    do
    {
        card = get_long("Card Number: ");
    }
    while (card < 1);

    // Check luhn
    bool luhn = check_luhn(card);

    // Report card type
    report_type(luhn, card);
}


bool check_luhn(long card)
{
    bool every_other_digit = 0;
    int checksum = 0;
    int i, n, digit;
    do
    {
        // Sum up digits
        if (!every_other_digit)
        {
            digit = (card % 10);
        }
        // Multiply every other digit by 2 and sum up digits
        else
        {
            n = card % 10 * 2;
            digit = (n > 9) ? n - 9 : n;
        }
        checksum += digit;
        card /= 10;
        every_other_digit = !every_other_digit;
    } while (card > 0);
    // Return True if checksum = 0
    bool luhn = checksum % 10 == 0;
    return luhn;
}


void report_type(bool luhn, long card)
{
    // Grab card prefix
    long prefix = card;
    do
    {
        prefix /= 10;
    } while (prefix > 100);
    
    // Calculate card length
    int length = 0;
    do
    {
        card /= 10;
        length++;
    } while (card > 0);
    
    // Print final result
    string type = "INVALID\n";
    if (luhn)
    {
        if (length == 16 && prefix > 50 && prefix < 56)
        {
            type = "MASTERCARD\n";
        }
        else if ((length == 13 || length == 16) && prefix /10 == 4)
        {
            type = "VISA\n";
        }
        else if (length == 15 && (prefix == 34 || prefix == 37))
        {
            type = "AMEX\n";
        }    
    }
    printf("%s", type);
}
