#include <stdio.h>
#include <cs50.h>
#include <string.h>

int main(void)
{
    string s = get_string("INPUT: ");

    printf("OUTPUT: ");
    // strlen(s) is total sum of the comparison whether s[i] != '\0'
    // '\0' represents NULL, the end of a string it's all 0 bits
    for(int i = 0, length = strlen(s); i < length; i++)
    {
        printf("%c", s[i]);
    }

    printf("\n");
}