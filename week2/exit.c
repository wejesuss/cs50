#include <cs50.h>
#include <stdio.h>

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("missing comand-line argument\n");
        return 1;
        // see this with echo $?
    }

    printf("%s\n", argv[1]);
    return 0;
    // see this with echo $?
}