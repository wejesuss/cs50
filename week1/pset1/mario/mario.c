#include <cs50.h>
#include <stdio.h>

int get_positive_int(string message, int minimum, int max);

int main(void)
{
    int minimum = 1;
    int max = 8;
    int height = get_positive_int("Write the height from %i to %i: ", 1, 8);
    int gap = 2;

    for (int row = 1; row <= height; row++)
    {
        int width = height + row + gap;
        int max_spaces_to_print = height - row;

        for (int column = 1; column <= width; column++)
        {

            if (column <= max_spaces_to_print)
            {
                printf(" ");
            }
            else
            {
                bool should_print_gap = column > height && column <= height + gap;

                if (should_print_gap)
                {
                    printf(" ");
                }
                else
                {
                    printf("#");
                }
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