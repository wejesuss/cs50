#include <cs50.h>
#include <string.h>
#include <stdio.h>

int main(int argc, string argv[])
{
    if (argv[1])
    {
        for (int i = 0, n = strlen(argv[1]); i < n; i++)
        {
            printf("%c\n", argv[1][i]);
        }
    }
}