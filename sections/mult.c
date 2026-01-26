#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>

int mult(int a, int b);

int main(int argc, string argv[])
{
    if (argc != 3)
    {
        printf("Error: Please enter 2 numbers\n");
        return 1;
    }
    else
    {
        int num1 = atoi(argv[1]);
        int num2 = atoi(argv[2]);
        printf("Answer = %i\n", mult(num1, num2));
    }
}

int mult(int a, int b)
{
    return a * b;
}
