// Prints a right-leaning pyramid of 8-height or less.

#include <cs50.h>
#include <stdio.h>

void print_row(int spaces, int bricks);

int main(void)
{
    // Prompt user for height of pyramid
    int height;
    do
    {
        height = get_int("Height: ");
    }
    while (height < 1);

    // Print a pyramid of that height
    for (int i = 0; i < height; i++)
    {
        print_row(height - i, i + 1);
    }
}

// Print a row of spaces and bricks
void print_row(int spaces, int bricks)
{
    // Print row of spaces
    for (int j = spaces - 1; j > 0; j--)
    {
        printf(" ");
    }

    // Print row of bricks
    for (int k = 0; k < bricks; k++)
    {
        printf("#");
    }
    printf("\n");
}
