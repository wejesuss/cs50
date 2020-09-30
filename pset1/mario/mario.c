#include <cs50.h>
#include <stdio.h>

int get_positive_int(string message, int minimum, int max);

int main(void)
{
    int minimum = 1;
    int max = 8;
    int height = get_positive_int("Write a number between %i and %i: ", 1, 8);

    for (int i = 1; i <= height; i++)
    {
        for (int j = 1; j <= height; j++)
        {
            int max_spaces_to_print = height - i;

            if (j <= max_spaces_to_print)
            {
                printf(" ");
            }
            else
            {
                printf("#");
            }
        }
        printf("\n");
    }
}

int get_positive_int(string message, int minimum, int max)
{
    int n;
    do
    {
        n = get_int(message, minimum, max);
    }
    while (n < minimum || n > max);

    return n;
}