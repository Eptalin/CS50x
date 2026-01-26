#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int average = (int) round(
                (image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.0);
            image[i][j].rgbtRed = average;
            image[i][j].rgbtGreen = average;
            image[i][j].rgbtBlue = average;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int sepiaRed = (int) round(image[i][j].rgbtRed * 0.393 + image[i][j].rgbtGreen * 0.769 +
                                       image[i][j].rgbtBlue * 0.189);
            if (sepiaRed > 255)
            {
                sepiaRed = 255;
            }
            int sepiaGreen =
                (int) round(image[i][j].rgbtRed * 0.349 + image[i][j].rgbtGreen * 0.686 +
                            image[i][j].rgbtBlue * 0.168);
            if (sepiaGreen > 255)
            {
                sepiaGreen = 255;
            }
            int sepiaBlue =
                (int) round(image[i][j].rgbtRed * 0.272 + image[i][j].rgbtGreen * 0.534 +
                            image[i][j].rgbtBlue * 0.131);
            if (sepiaBlue > 255)
            {
                sepiaBlue = 255;
            }

            image[i][j].rgbtRed = sepiaRed;
            image[i][j].rgbtGreen = sepiaGreen;
            image[i][j].rgbtBlue = sepiaBlue;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < (width / 2); j++)
        {
            int temp = image[i][j].rgbtRed;
            image[i][j].rgbtRed = image[i][(width - 1) - j].rgbtRed;
            image[i][(width - 1) - j].rgbtRed = temp;

            temp = image[i][j].rgbtGreen;
            image[i][j].rgbtGreen = image[i][(width - 1) - j].rgbtGreen;
            image[i][(width - 1) - j].rgbtGreen = temp;

            temp = image[i][j].rgbtBlue;
            image[i][j].rgbtBlue = image[i][(width - 1) - j].rgbtBlue;
            image[i][(width - 1) - j].rgbtBlue = temp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Make a copy of the image to work with
    RGBTRIPLE copy[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }

    // Initialise variables
    float counter = 0.0;

    int tallyRed = 0;
    int tallyGreen = 0;
    int tallyBlue = 0;

    // Iterate over each pixel on row i and column j
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Iterate over the surrounding pixels
            for (int x = -1; x <= 1; x++)
            {
                for (int y = -1; y <= 1; y++)
                {
                    // Check if the pixel is within bounds, increment the counter, and add the RGB
                    // values to the total
                    if (i + x >= 0 && i + x < height && j + y >= 0 && j + y < width)
                    {
                        counter += 1.0;
                        tallyRed += copy[i + x][j + y].rgbtRed;
                        tallyGreen += copy[i + x][j + y].rgbtGreen;
                        tallyBlue += copy[i + x][j + y].rgbtBlue;
                    }
                }
            }

            // Calculate the average RGB values and apply them to the original image
            image[i][j].rgbtRed = (int) round(tallyRed / counter);
            image[i][j].rgbtGreen = (int) round(tallyGreen / counter);
            image[i][j].rgbtBlue = (int) round(tallyBlue / counter);

            counter = 0.0;
            tallyRed = 0;
            tallyGreen = 0;
            tallyBlue = 0;
        }
    }
    return;
}
