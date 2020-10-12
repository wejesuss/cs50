#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

string encrypt_text(string plaintext, int key);
int calculate_secure_sum(char c, int key);
char encrypt_alphabetic_character(char c, int limit_to_sum, int key);
char encrypt_alphabetic_and_non_alphabetic(char c, int key);

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
        ciphertext[i] = encrypt_alphabetic_and_non_alphabetic(c, key);
    }

    return ciphertext;
}

char encrypt_alphabetic_and_non_alphabetic(char c, int key)
{
    if (isalpha(c))
    {
        int limit_to_sum = calculate_secure_sum(c, key);
        return encrypt_alphabetic_character(c, limit_to_sum, key);
    }

    return c;
}

char encrypt_alphabetic_character(char c, int limit_to_sum, int key)
{
    int alphabet_length = 26;

    if ((int) c <= limit_to_sum)
    {
        return (int) c + key;
    }

    return (int) c + key - alphabet_length;
}

int calculate_secure_sum(char c, int key)
{
    int lowercase_z_in_decimal = 122;
    int uppercase_z_in_decimal = 90;

    if (islower(c))
    {
        return lowercase_z_in_decimal - key;
    }

    return uppercase_z_in_decimal - key;
}