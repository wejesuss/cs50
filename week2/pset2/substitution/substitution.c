#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

int validate_key(string key, int length);
string encrypt_text(string plaintext, string key);

int main(int argc, string argv[])
{
    string program = argv[0];
    if (argc != 2)
    {
        printf("Usage %s key\n", program);
        return 1;
    }

    string key = argv[1];
    int length = strlen(key);

    if (length != 26)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }

    if (!validate_key(key, length))
    {
        printf("Usage %s key\n", program);
        return 1;
    }

    string plaintext = get_string("plaintext: ");

    string ciphertext = encrypt_text(plaintext, key);

    printf("ciphertext: %s\n", ciphertext);
}

string encrypt_text(string plaintext, string key)
{
    int length = strlen(plaintext);
    string ciphertext = plaintext;

    for (int i = 0; i < length; i++)
    {
        char plain_c = plaintext[i];
        if (isalpha(plain_c))
        {
            char cipher_c = ciphertext[i];
            if (islower(cipher_c))
            {
                int position = (int) cipher_c - 97;
                char key_c = key[position];
                cipher_c = tolower(key_c);
            }
            else
            {
                int position = (int) cipher_c - 65;
                char key_c = key[position];
                cipher_c = toupper(key_c);
            }

            ciphertext[i] = cipher_c;
        }
        else
        {
            ciphertext[i] = plain_c;
        }
    }

    return ciphertext;
}

int validate_key(string key, int length)
{
    for (int i = 0, j = length - 1; i < length && j > i; j--)
    {
        char left = toupper(key[i]);
        if (!isalpha(left))
        {
            return 0;
        }

        char right = toupper(key[j]);
        if (right == left)
        {
            return 0;
        }

        if (j - 1 == i)
        {
            j = length;
            i++;
        }
    }

    return 1;
}