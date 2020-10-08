#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

int calculate_letters(char character);
int calculate_words(char character);
int calculate_sentences(char character);
int calculate_grade(int letters, int sentences, int words);
float average_per_hundred(int multiplier, int divider);
string give_result(int grade);

int main(void)
{
    string s = get_string("Text: ");

    int letters = 0;
    int words = 0;
    int sentences = 0;

    for (int i = 0, length = strlen(s); i <= length; i++)
    {
        char c = s[i];

        letters += calculate_letters(c);
        words += calculate_words(c);
        sentences += calculate_sentences(c);
    }

    if (letters > 0)
    {
        words++;
    }

    int grade = calculate_grade(letters, sentences, words);

    string result = give_result(grade);

    if(grade < 1 || grade >= 16)
    {
        printf("%s\n", result);
    }
    else
    {
        printf("%s %i\n", result, grade);
    }

}

int calculate_letters(char character)
{
    int value = 0;
    if (isalpha(character))
    {
        value = 1;
    }

    return value;
}

int calculate_words(char character)
{
    int value = 0;
    if (isspace(character))
    {
        value = 1;
    }

    return value;
}

int calculate_sentences(char character)
{
    int value = 0;
    bool is_sentence = character == '.' || character == '?' || character == '!';
    if (is_sentence)
    {
        value = 1;
    }

    return value;
}

int calculate_grade(int letters, int sentences, int words)
{
    float average_letters = average_per_hundred(letters, words);
    float average_sentences = average_per_hundred(sentences, words);

    return round(0.0588 * average_letters - 0.296 * average_sentences - 15.8);
}

float average_per_hundred(int multiplier, int divider)
{
    return (100.0 * multiplier) / divider;
}

string give_result(int grade)
{
    if (grade < 1)
    {
        return "Before Grade 1";
    }

    if (grade >= 16)
    {
        return "Grade 16+";
    }

    return "Grade";
}