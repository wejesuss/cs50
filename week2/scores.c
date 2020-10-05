#include <stdio.h>
#include <cs50.h>

float average(int length, int array[]);


int main(void)
{
    int n;
    do {
        n = get_int("total: ");
    }
    while (n < 1);

    const int TOTAL = n;
    int scores[TOTAL];

    for(int i = 0; i < TOTAL; i++)
    {
        scores[i] = get_int("Score: ");
    }

    printf("Average: %f\n", average(TOTAL, scores));
}

float average(int length, int array[])
{
    int total = 0;
    for(int i = 0; i < length; i++)
    {
        total += array[i];
    }

    return total / (float) length;
}