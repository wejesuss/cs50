#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

int compute_score(string word);
string verify_result(int score1, int score2);

const int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};
const int DISTANCE_TO_A_ASCII = 65;

int main(void)
{
    string word1 = get_string("Player 1: ");
    string word2 = get_string("Player 2: ");

    int score1 = compute_score(word1);
    int score2 = compute_score(word2);

    string result = verify_result(score1, score2);

    printf("%s\n", result);
}

int compute_score(string word)
{
    int score = 0;

    for (int i = 0, length = strlen(word); i < length; i++)
    {
        char c = toupper(word[i]);

        if (c >= 'A' && c <= 'Z')
        {
            score += POINTS[c - DISTANCE_TO_A_ASCII];
        }
    }

    return score;
}

string verify_result(int score1, int score2)
{
    if (score1 > score2)
    {
        return "Player 1 wins!";
    }
    else if (score2 > score1)
    {
        return "Player 2 wins!";
    }
    else
    {
        return "Tie!";
    }
}