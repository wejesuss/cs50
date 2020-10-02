#include <cs50.h>
#include <stdio.h>

long get_valid_long(string message);
int get_first_two_digits(int credit_number);
int sum_of_tens(int tens);
string check_credit_card(int length, int first_two_digits, int checksum);

int main(void)
{
    long credit_number = get_valid_long("Number: ");
    int last_digit, checksum, first_two_digits;
    int odd_digits_sum = 0;
    int even_digits_sum = 0;
    int length = 0;

    do
    {
        last_digit = credit_number % 10;

        if (credit_number > 9)
        {
            first_two_digits = get_first_two_digits(credit_number);
        }

        if (length % 2 > 0)
        {
            last_digit *= 2;
            odd_digits_sum += sum_of_tens(last_digit);
        }
        else
        {
            even_digits_sum += last_digit;
        }

        credit_number /= 10;
        length++;
    }
    while (credit_number > 0);

    checksum = (odd_digits_sum + even_digits_sum) % 10;

    string result = check_credit_card(length, first_two_digits, checksum);

    printf("%s\n", result);
}

long get_valid_long(string message)
{
    return get_long("%s", message);
}

int get_first_two_digits(int credit_number)
{
    return credit_number % 100;
}

int sum_of_tens(int tens)
{
    return (tens % 10) + (tens / 10);
}

string check_credit_card(int length, int first_two_digits, int checksum)
{
    bool incorrect_length = length < 13 || length == 14 || length > 16;
    bool incorrect_checksum = checksum != 0;

    bool amex = length == 15 && (first_two_digits == 34 || first_two_digits == 37);
    bool visa = (length == 13 || length == 16) && ((first_two_digits / 10) == 4);
    bool mastercard = length == 16 && (first_two_digits > 50 && first_two_digits < 56);

    if (incorrect_length || incorrect_checksum)
    {
        return "INVALID";
    }

    if (amex)
    {
        return "AMEX";
    }

    if (visa)
    {
        return "VISA";
    }

    if (mastercard)
    {
        return "MASTERCARD";
    }

    return "INVALID";
}
