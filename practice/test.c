#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, string argv[])
{
    // Convert string array to integer array
    int numbers[argc - 1];
    for (int n = 1; n < argc; n++)
    {
        numbers[n - 1] = atoi(argv[n]);
    }

    // Sort list using bubble sort
    for (int swaps = -1; swaps != 0;)
    {
        swaps = 0;
        for (int i = 0; i < argc - 2; i++)
        {
            if (numbers[i + 1] < numbers[i])
            {
                int temp = numbers[i];
                numbers[i] = numbers[i + 1];
                numbers[i + 1] = temp;
                swaps += 1;
            }
        }
    }

    // Print sorted list
    for (int j = 0; j < argc - 1; j++)
    {
        printf("%i ", numbers[j]);
    }
    printf("\n");
}
