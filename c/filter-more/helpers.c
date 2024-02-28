#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; ++i)
    {
        for (int j = 0; j < width; ++j)
        {
            uint8_t gscolor;
            gscolor = round((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0);
            image[i][j].rgbtBlue = gscolor;
            image[i][j].rgbtGreen = gscolor;
            image[i][j].rgbtRed = gscolor;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; ++i)
    {
        for (int j = 0; j < width / 2; ++j)
        {
            RGBTRIPLE tmp;
            tmp = image[i][j];
            image[i][j] = image[i][width - 1 - j];
            image[i][width - 1 - j] = tmp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int sumBlue = 0;
            int sumGreen = 0;
            int sumRed = 0;
            int counter = 0;

            for (int k = -1; k < 2; k++)
            {
                for (int h = -1; h < 2; h++)
                {
                    if (i + k < 0 || i + k >= height || j + h < 0 || j + h >= width)
                    {
                        continue;
                    }

                    sumBlue += image[i + k][j + h].rgbtBlue;
                    sumGreen += image[i + k][j + h].rgbtGreen;
                    sumRed += image[i + k][j + h].rgbtRed;
                    counter++;
                }
            }

            temp[i][j].rgbtBlue = round((float) sumBlue / counter);
            temp[i][j].rgbtGreen = round((float) sumGreen / counter);
            temp[i][j].rgbtRed = round((float) sumRed / counter);
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = temp[i][j];
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    int gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

    RGBTRIPLE temp[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int sumBlueX = 0;
            int sumGreenX = 0;
            int sumRedX = 0;

            for (int k = -1; k < 2; k++)
            {
                for (int h = -1; h < 2; h++)
                {
                    if (i + k < 0 || i + k >= height || j + h < 0 || j + h >= width)
                    {
                        continue;
                    }

                    sumBlueX += image[i + k][j + h].rgbtBlue * gx[k + 1][h + 1];
                    sumGreenX += image[i + k][j + h].rgbtGreen * gx[k + 1][h + 1];
                    sumRedX += image[i + k][j + h].rgbtRed * gx[k + 1][h + 1];
                }
            }

            int sumBlueY = 0;
            int sumGreenY = 0;
            int sumRedY = 0;

            for (int k = -1; k < 2; k++)
            {
                for (int h = -1; h < 2; h++)
                {
                    if (i + k < 0 || i + k >= height || j + h < 0 || j + h >= width)
                    {
                        continue;
                    }

                    sumBlueY += image[i + k][j + h].rgbtBlue * gy[k + 1][h + 1];
                    sumGreenY += image[i + k][j + h].rgbtGreen * gy[k + 1][h + 1];
                    sumRedY += image[i + k][j + h].rgbtRed * gy[k + 1][h + 1];
                }
            }

            int r, g, b;
            b = round(sqrt(sumBlueX * sumBlueX + sumBlueY * sumBlueY));
            g = round(sqrt(sumGreenX * sumGreenX + sumGreenY * sumGreenY));
            r = round(sqrt(sumRedX * sumRedX + sumRedY * sumRedY));
            temp[i][j].rgbtBlue = b > 255 ? 255 : b;
            temp[i][j].rgbtGreen = g > 255 ? 255 : g;
            temp[i][j].rgbtRed = r > 255 ? 255 : r;
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = temp[i][j];
        }
    }
    return;
}
