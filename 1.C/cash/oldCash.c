#include <cs50.h>
#include <stdio.h>

int calc_coins(int change);

int main(void)
{
    int change;
    do
    {
        change = get_int("Change: ");
    }
    while (change < 0);

    int coins = calc_coins(change);
    printf("%i\n", coins);
}

int calc_coins(int change)
{
    int coin_value[4] = {25, 10, 5, 1};
    int n = 0;

    for (int i = 0; i < 4; i++)
    {
        n += change / coin_value[i];
        change -= coin_value[i] * (change / coin_value[i]);
    }
    return n;
}
