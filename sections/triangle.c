#include <cs50.h>
#include <stdio.h>

bool valid_triangle(float a, float b, float c);

int main(void)
{
    // Get user input for the 3 side lengths
    float x = get_float("Length of Side 1: ");
    float y = get_float("Length of Side 2: ");
    float z = get_float("Length of Side 3: ");

    if (valid_triangle(x, y, z) == 0)
    {
        printf("The triangle is not valid\n");
    }
    else if (valid_triangle(x, y, z) == 1)
    {
        printf("The triangle is valid\n");
    }
    else
    {
        return 1;
    }
}

bool valid_triangle(float a, float b, float c)
{
    if (a <= 0 || b <= 0 || c <= 0)
    {
        return false;
    }
    else if ((a + b) <= c || (b + c) <= a || (c + a) <= b)
    {
        return false;
    }
    else
    {
        return true;
    }
}
