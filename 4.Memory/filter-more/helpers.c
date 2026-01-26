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
                    // Check if the pixel is within bounds, increment the counter, 
                    // and add the RGB values to the tally
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

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
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
    int Gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int Gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};
    int GxRed = 0;
    int GxGreen = 0;
    int GxBlue = 0;
    int GyRed = 0;
    int GyGreen = 0;
    int GyBlue = 0;
    int value_red;
    int value_green;
    int value_blue;

    // Iterate over each pixel
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Iterate over the pixels surrounding each pixel
            for (int x = -1; x <= 1; x++)
            {
                for (int y = -1; y <= 1; y++)
                {
                    // Check if pixel is inside the bounds of the image
                    if (i + x >= 0 && i + x < height && j + y >= 0 && j + y < width)
                    {
                        GxRed += copy[i + x][j + y].rgbtRed * Gx[x + 1][y + 1];
                        GxGreen += copy[i + x][j + y].rgbtGreen * Gx[x + 1][y + 1];
                        GxBlue += copy[i + x][j + y].rgbtBlue * Gx[x + 1][y + 1];

                        GyRed += copy[i + x][j + y].rgbtRed * Gy[x + 1][y + 1];
                        GyGreen += copy[i + x][j + y].rgbtGreen * Gy[x + 1][y + 1];
                        GyBlue += copy[i + x][j + y].rgbtBlue * Gy[x + 1][y + 1];
                    }
                }
            }
            // Sobel filter algorithm
            value_red = (int) round(sqrt((GxRed * GxRed) + (GyRed * GyRed)));
            if (value_red < 255)
            {
                image[i][j].rgbtRed = value_red;
            }
            else
            {
                image[i][j].rgbtRed = 255;
            }

            value_green = (int) round(sqrt((GxGreen * GxGreen) + (GyGreen * GyGreen)));
            if (value_green < 255)
            {
                image[i][j].rgbtGreen = value_green;
            }
            else
            {
                image[i][j].rgbtGreen = 255;
            }

            value_blue = (int) round(sqrt((GxBlue * GxBlue) + (GyBlue * GyBlue)));
            if (value_blue < 255)
            {
                image[i][j].rgbtBlue = value_blue;
            }
            else
            {
                image[i][j].rgbtBlue = 255;
            }

            // Reset values to 0
            GxRed = 0;
            GxGreen = 0;
            GxBlue = 0;
            GyRed = 0;
            GyGreen = 0;
            GyBlue = 0;
        }
    }
    return;
}
