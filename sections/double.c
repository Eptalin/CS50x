#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // Prompt user for length of sequence
    int length = get_int ("Enter a length: ");
    int sequence[length];

    // Print a sequence of numbers that double each step
    sequence[0] = 1;
    printf("%i\n", sequence[0]);

    for (int i = 1; i < length; i++)
    {
        sequence[i] = sequence[i - 1] * 2;
        printf("%i\n", sequence[i]);
    }
}
