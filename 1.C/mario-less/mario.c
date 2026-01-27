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
    for (int row = 1; row <= height; row++)
    {
        print_row(height - row, row);
    }
}


// Print a row of spaces and bricks
void print_row(int spaces, int bricks)
{
    for (int i = 0; i < spaces + bricks; i++)
    {
        char c = (i < spaces) ? ' ' : '#';
        printf("%c", c);
    }
    printf("\n");
}
