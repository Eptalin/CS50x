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
                (image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.0
            );
            image[i][j].rgbtRed = average;
            image[i][j].rgbtGreen = average;
            image[i][j].rgbtBlue = average;
        }
    }
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
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < (width / 2); j++)
        {
            RGBTRIPLE temp = image[i][j];
            image[i][j] = image[i][(width - 1) - j];
            image[i][(width - 1) - j] = temp;
        }
    }
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

    // Iterate over each pixel on row i and column j
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Initialise variables
            int counter = 0;
            int tallyRed = 0, tallyGreen = 0, tallyBlue = 0;

            // Iterate over the surrounding pixels
            for (int x = -1; x <= 1; x++)
            {
                for (int y = -1; y <= 1; y++)
                {
                    // Check if pixel within bounds, increment the counter, and
                    // add RGB values to sums
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
            image[i][j].rgbtRed = round(tallyRed / (float) counter);
            image[i][j].rgbtGreen = round(tallyGreen / (float) counter);
            image[i][j].rgbtBlue = round(tallyBlue / (float) counter);
        }
    }
}
