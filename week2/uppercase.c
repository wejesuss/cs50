#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

int main(void)
{
    string s = get_string("BEFORE: ");

    printf("AFTER: ");
    for(int i = 0, length = strlen(s); i < length; i++)
    {
        printf("%c", toupper(s[i]));
        // uppercase english letters are 32 bits fewer than this lowercase one
    }

    printf("\n");
}