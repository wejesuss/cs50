#include <cs50.h>
#include <stdio.h>

int get_minimum_int(int minimum, string message);

int main(void)
{
    long startSize;
    long endSize;
    int years = 0;
    int minimumSize = 9;

    startSize = get_minimum_int(minimumSize, "Start size of the population (greater or equal to %i): ");

    printf("\n");

    endSize = get_minimum_int(startSize, "End size of the population (greater or equal to %i): ");

    printf("\n");

    int population = startSize;

    while (population < endSize)
    {
        int growth = population / 3;
        int shrank = population / 4;
        int change = growth - shrank;

        population += change;
        years++;
    }

    printf("Years: %i\n", years);
}

int get_minimum_int(int minimum, string message)
{
    int n;
    do
    {
        n = get_int(message, minimum);
    }
    while (n < minimum);

    return n;
}