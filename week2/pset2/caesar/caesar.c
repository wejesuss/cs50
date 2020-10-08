#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

string encrypt_text(string plaintext, int key);

int main(int argc, string argv[])
{
    string program = argv[0];
    if (argc != 2)
    {
        printf("Usage %s key\n", program);
        return 1;
    }

    string key = argv[1];
    for (int i = 0, n = strlen(key); i < n; i++)
    {
        char c = key[i];
        if (!isdigit(c))
        {
            printf("Usage %s key\n", program);
            return 1;
        }
    }

    int n_key = atoi(key) % 26;
    string plaintext = get_string("plaintext: ");
    string ciphertext = encrypt_text(plaintext, n_key);

    printf("ciphertext: %s\n", ciphertext);
}

string encrypt_text(string plaintext, int key)
{
    string ciphertext = plaintext;
    for (int i = 0, length = strlen(plaintext); i < length; i++)
    {
        char c = plaintext[i];
        if (isalpha(c))
        {
            int limit_to_sum;
            if (islower(c))
            {
                limit_to_sum = 122 - key;
            }
            else
            {
                limit_to_sum = 90 - key;
            }

            if ((int) c <= limit_to_sum)
            {
                ciphertext[i] = (int) c + key;
            }
            else
            {
                ciphertext[i] = (int) c + key - 26;
            }
        }
        else
        {
            ciphertext[i] = c;
        }
    }

    return ciphertext;
}