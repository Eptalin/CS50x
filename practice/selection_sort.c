#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, string argv[])
{
    // Convert string array to integer array
    int sequence[argc];
    for (int n = 1; n < argc; n++)
    {
        sequence[n] = atoi(argv[n]);
    }

    // Sort list using selection sort
    for (int i = 1; i < argc; i++)
    {
        int min = i;
        for (int j = i + 1; j < argc; j++)
        {
            if (sequence[j] < sequence[min])
            {
                min = j;
            }
        }
        if (min != i)
        {
            int temp = sequence[i];
            sequence[i] = sequence[min];
            sequence[min] = temp;
        }
    }

    // Print sorted list
    for (int k = 1; k < argc; k++)
    {
        printf("%i ", sequence[k]);
    }
    printf("\n");
}
