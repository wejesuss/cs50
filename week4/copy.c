#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

int main(void)
{
    char * s = get_string("s: ");
    int n = strlen(s);
    char * t = malloc(n + 1);

    if (t == NULL)
    {
        return 1;
    }

    strcpy(t, s);

    if (n > 0)
    {
        t[0] = toupper(t[0]);
    }

    printf("%s\n", s);
    printf("%s\n", t);

    free(t);
    return 0;
}