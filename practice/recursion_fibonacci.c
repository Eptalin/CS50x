#include <cs50.h>
#include <stdio.h>

// Function prorotypes
int collatz(int n);

int main(void)
{
    int x = get_int("Enter number: ");
    printf("%i\n", collatz(x));
}

// Calculate how many steps it takes to get to 1
int collatz(int n)
{
    // Base case
    if (n == 1)
        return 0;
    // Even numbers
    else if (n % 2 == 0)
        return 1 + collatz(n / 2);
    // Odd numbers
    else
    return 1 + collatz(3 * n + 1);
}
