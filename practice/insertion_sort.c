#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>

void insertion_sort(int array[], int n);

// Usage: "./insertion_sort 1 9 2 8 3 4 7 5 3 6"
int main(int argc, string argv[])
{
    int n = argc - 1;
    // Convert string array to int array
    int numbers[argc - 1];
    for (int i = 0; i < argc - 1; i++)
    {
        numbers[i] = atoi(argv[i + 1]);
    }

    insertion_sort(numbers, n);

    // Print the sorted list
    for (int i = 0; i < argc - 1; i++)
    {
        printf("%i ", numbers[i]);
    }
    printf("\n");
}

void insertion_sort(int array[], int n)
{
    // Iterate over numbers (First is already "sorted")
    for (int i = 1; i < n; i++)
    {
        // Store current element to be inserted
        int key = array[i];
        // Store the index of the last "sorted" element
        int j = i - 1;

        // Shift elements in "sorted" section to the right to make space
        while (j >= 0 && array[j] > key)
        {
            // Move larger element to right, then move one element left
            array[j + 1] = array[j];
            j--;
        }

        // Insert current element into correct position
        array[j + 1] = key;

    }
    return;
}
