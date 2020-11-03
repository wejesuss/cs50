#include <math.h>
#include "helpers.h"

// Auxiliary function to calculate sepia color
int calcSepia(int red, int green, int blue, char type);

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    int red, green, blue;
    for (int i = 0, j = width - 1; i < height && j >= 0; j--)
    {
        red = image[i][j].rgbtRed;
        green = image[i][j].rgbtGreen;
        blue = image[i][j].rgbtBlue;

        int average = round((red + green + blue) / 3.0);

        image[i][j].rgbtRed = average;
        image[i][j].rgbtGreen = average;
        image[i][j].rgbtBlue = average;

        if (j == 0)
        {
            j = width;
            i++;
        }
    }

    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    int red, green, blue, sepiaRed, sepiaGreen, sepiaBlue;

    for (int i = 0, j = width - 1; i < height && j >= 0; j--)
    {
        red = image[i][j].rgbtRed;
        green = image[i][j].rgbtGreen;
        blue = image[i][j].rgbtBlue;

        sepiaRed = calcSepia(red, green, blue, 'r');
        sepiaGreen = calcSepia(red, green, blue, 'g');
        sepiaBlue = calcSepia(red, green, blue, 'b');

        image[i][j].rgbtRed = sepiaRed;
        image[i][j].rgbtGreen = sepiaGreen;
        image[i][j].rgbtBlue = sepiaBlue;

        if (j == 0)
        {
            j = width;
            i++;
        }
    }

    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE pixel;

    for (int i = 0, hi = width - 1, lo = 0; i < height; hi--, lo++)
    {
        if (hi == lo || hi < lo)
        {
            hi = width;
            lo = -1;
            i++;
            continue;
        }

        pixel = image[i][hi];
        image[i][hi] = image[i][lo];
        image[i][lo] = pixel;
    }

    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE center, center_left, center_right;
    RGBTRIPLE upper_center, upper_left, upper_right;
    RGBTRIPLE bottom_center, bottom_left, bottom_right;

    RGBTRIPLE new_image[height][width];

    for (int i = 0, j = 0; i < height; j++)
    {
        float red = 0, green = 0, blue = 0, count = 1.0;

        center = image[i][j];

        red += center.rgbtRed;
        green += center.rgbtGreen;
        blue += center.rgbtBlue;

        if (j - 1 >= 0)
        {
            center_left = image[i][j - 1];
            red += center_left.rgbtRed;
            green += center_left.rgbtGreen;
            blue += center_left.rgbtBlue;
            count++;
        }

        if (j + 1 < width)
        {
            center_right = image[i][j + 1];
            red += center_right.rgbtRed;
            green += center_right.rgbtGreen;
            blue += center_right.rgbtBlue;
            count++;
        }

        if (i - 1 >= 0)
        {
            bottom_center = image[i - 1][j];
            red += bottom_center.rgbtRed;
            green += bottom_center.rgbtGreen;
            blue += bottom_center.rgbtBlue;
            count++;
        }

        if (i + 1 < height)
        {
            upper_center = image[i + 1][j];
            red += upper_center.rgbtRed;
            green += upper_center.rgbtGreen;
            blue += upper_center.rgbtBlue;
            count++;
        }

        if (i - 1 >= 0 && j - 1 >= 0)
        {
            bottom_left = image[i - 1][j - 1];
            red += bottom_left.rgbtRed;
            green += bottom_left.rgbtGreen;
            blue += bottom_left.rgbtBlue;
            count++;
        }

        if (i + 1 < height && j + 1 < width)
        {
            upper_right = image[i + 1][j + 1];
            red += upper_right.rgbtRed;
            green += upper_right.rgbtGreen;
            blue += upper_right.rgbtBlue;
            count++;
        }

        if (i + 1 < height && j - 1 >= 0)
        {
            upper_left = image[i + 1][j - 1];
            red += upper_left.rgbtRed;
            green += upper_left.rgbtGreen;
            blue += upper_left.rgbtBlue;
            count++;
        }

        if (i - 1 >= 0 && j + 1 < width)
        {
            bottom_right = image[i - 1][j + 1];
            red += bottom_right.rgbtRed;
            green += bottom_right.rgbtGreen;
            blue += bottom_right.rgbtBlue;
            count++;
        }

        new_image[i][j].rgbtRed = round(red / count);
        new_image[i][j].rgbtGreen = round(green / count);
        new_image[i][j].rgbtBlue = round(blue / count);

        if (j + 1 == width)
        {
            j = -1;
            i++;
        }
    }

    for (int i = 0, j = 0; i < height; j++)
    {
        image[i][j] = new_image[i][j];

        if (j + 1 == width)
        {
            j = -1;
            i++;
        }
    }

    return;
}

int calcSepia(int red, int green, int blue, char type)
{
    int sepia;
    switch (type)
    {
        case 'r':
            sepia = round(.393 * red + .769 * green + .189 * blue);
            break;

        case 'g':
            sepia = round(.349 * red + .686 * green + .168 * blue);
            break;

        case 'b':
            sepia = round(.272 * red + .534 * green + .131 * blue);
            break;
    }

    if (sepia > 255)
    {
        sepia = 255;
    }

    return sepia;
}
