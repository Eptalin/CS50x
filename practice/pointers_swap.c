#include <cs50.h>
#include <stdio.h>

void swap(int *a, int *b);

int main(void)
{
    // Prompt user for 2 integers
    int x = get_int("1st number: ");
    int y = get_int("2nd number: ");

    // Send the addresses of the 2 integers using &
    swap(&x, &y);

    printf("1st number: %i\n2nd number: %i\n", x, y);
}

void swap(int *a, int *b)
{
    // Use * to access the values stored at the addresses
    int temp = *a;
    *a = *b;
    *b = temp;
}
