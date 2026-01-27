// Prints double pyramids with a space between
#include <cs50.h>
#include <stdio.h>

void print_row(int spaces, int bricks);

int main(void)
{
    // Prompt user for height between 1 and 8
    int height;
    do
    {
        height = get_int("Height: ");
    }
    while (height < 1 || height > 8);

    // Print pyramids of that height
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

    // Print row of bricks 1
    for (int k = 0; k < bricks; k++)
    {
        printf("#");
    }

    // Print 2 spaces
    printf("  ");

    // Print row of bricks 2
    for (int l = 0; l < bricks; l++)
    {
        printf("#");
    }
    printf("\n");
}
