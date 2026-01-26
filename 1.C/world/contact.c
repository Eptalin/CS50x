#include <cs50.h>
#include <stdio.h>

int main(void)
{
    string name = get_string("What is the contact's name? ");
    int age = get_int("What is your age? ");
    string phone_number = get_string("What is your phone number? ");
    printf("Contact: %s\n %i\n %s\n", name, age, phone_number);
}
