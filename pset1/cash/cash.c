#include <cs50.h>
#include <math.h>
#include <stdio.h>

int calculate_change(int change, int coin);
float get_positive_float(string message);

int main(void)
{
    int total_coins = 0;
    int quarters = 25;
    int dimes = 10;
    int nickels = 5;
    int pennies = 1;

    int change = round(get_positive_float("Change owed: ") * 100);

    while (change > 0)
    {
        bool quarter = (change - quarters) >= 0;
        bool dime = (change - dimes) >= 0;
        bool nickel = (change - nickels) >= 0;
        bool penny = (change - pennies) >= 0;

        if (quarter)
        {
            change = calculate_change(change, quarters);
            total_coins++;
            continue;
        }

        if (dime)
        {
            change = calculate_change(change, dimes);
            total_coins++;
            continue;
        }

        if (nickel)
        {
            change = calculate_change(change, nickels);
            total_coins++;
            continue;
        }

        if (penny)
        {
            change = calculate_change(change, pennies);
            total_coins++;
            continue;
        }
    }

    printf("%i\n", total_coins);
}

int calculate_change(int change, int coin)
{
    return change - coin;
}

float get_positive_float(string message)
{
    float n;
    do
    {
        n = get_float("%s", message);
    }
    while (n <= 0);

    return n;
}

