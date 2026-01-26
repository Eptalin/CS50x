#include <cs50.h>
#include <stdio.h>

// Function prorotypes
int factorial(int n);

int main(void)
{
    // Prompt user for number
    int x = get_int("Enter a number: ");

    // Calculate and print the factorial of that number
    printf("%i\n", factorial(x));
}

int factorial(int n)
{
    if (n == 1)
        return 1;
    else
        return n * factorial(n-1);
}
