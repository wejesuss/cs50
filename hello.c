#include <cs50.h>
#include <stdio.h>

// prototype
void meow(int n);

int main(void)
{
    int times = get_int("How many times? ");
    meow(times);
}

void meow(int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("meow\n");
    }
}