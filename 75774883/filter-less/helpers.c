#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++) // control height (row)
    {
        for (int j = 0; j < width; j++) // control width (column)
        {
            float average = round((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0); // find average of 3 color
            image[i][j].rgbtBlue = (int) average;                                                         // set it all the same
            image[i][j].rgbtGreen = (int) average;
            image[i][j].rgbtRed = (int) average;
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
            int sepiaRed = round(.393 * image[i][j].rgbtRed + .769 * image[i][j].rgbtGreen + .189 * image[i][j].rgbtBlue);
            sepiaRed = sepiaRed > 255 ? 255 : sepiaRed;
            int sepiaGreen = round(.349 * image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen + .168 * image[i][j].rgbtBlue);
            sepiaGreen = sepiaGreen > 255 ? 255 : sepiaGreen;
            int sepiaBlue = round(.272 * image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen + .131 * image[i][j].rgbtBlue);
            sepiaBlue = sepiaBlue > 255 ? 255 : sepiaBlue;

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
            RGBTRIPLE buffer = image[i][j];
            image[i][j] = image[i][width - (j + 1)];
            image[i][width - (j + 1)] = buffer;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    //copy a picture to
    RGBTRIPLE copy[height][width];
    for (int i = 0; i < height; i++) // control height (row)
    {
        for (int j = 0; j < width; j++) // control width (column)
        {
            copy[i][j] = image[i][j]; // make a copy byte
        }
    }

    // inner-square (has 9 around them) or the star
    //  -----
    //  -***-
    //  -***-
    //  -***-
    //  -----
    for (int i = 1; i < height - 1; i++)
    {
        for (int j = 1; j < width - 1; j++)
        {
            float average_red = 0, average_green = 0, average_blue = 0;
            for (int m = 1; m > -2; m--)
            {
                // row of around
                for (int n = 1; n > -2; n--)
                {
                    // col of around
                    average_red += copy[i + m][j + n].rgbtRed;
                    average_green += copy[i + m][j + n].rgbtGreen;
                    average_blue += copy[i + m][j + n].rgbtBlue;
                }
            }
            image[i][j].rgbtRed = (int) round(average_red / 9.0);
            image[i][j].rgbtGreen = (int) round(average_green / 9.0);
            image[i][j].rgbtBlue = (int) round(average_blue / 9.0);
        }
    }

    // left-top corner (0, 0)
    float average_red = 0, average_green = 0, average_blue = 0;
    for (int i = 0; i < 2; i++)
    {
        // pattern for row 0 -> 1

        for (int j = 0; j < 2; j++)
        {
            // pattern for col 0 -> 1
            average_red += copy[i][j].rgbtRed;
            average_green += copy[i][j].rgbtGreen;
            average_blue += copy[i][j].rgbtBlue;
        }
    }
    image[0][0].rgbtRed = (int) round(average_red / 4.0);
    image[0][0].rgbtGreen = (int) round(average_green / 4.0);
    image[0][0].rgbtBlue = (int) round(average_blue / 4.0);

    // right-top corner (0 , width - 1)
    average_red = 0, average_green = 0, average_blue = 0;
    // pattern for row 0 -> -1
    for (int i = 0; i < 2; i++)
    {
        // pattern for col -1 -> 0
        for (int j = -1; j < 1; j++)
        {
            average_red += copy[i][width - 1 + j].rgbtRed;
            average_green += copy[i][width - 1 + j].rgbtGreen;
            average_blue += copy[i][width - 1 + j].rgbtBlue;
        }
    }
    image[0][width - 1].rgbtRed = (int) round(average_red / 4.0);
    image[0][width - 1].rgbtGreen = (int) round(average_green / 4.0);
    image[0][width - 1].rgbtBlue = (int) round(average_blue / 4.0);

    // left-bottom corner (height - 1, 0)
    average_red = 0, average_green = 0, average_blue = 0;
    for (int i = -1; i < 1; i++)
    {
        // pattern for row -1 -> 0
        for (int j = 0; j < 2; j++)
        {
            // pattern for row 0 -> 1
            average_red += copy[height - 1 + i][j].rgbtRed;
            average_green += copy[height - 1 + i][j].rgbtGreen;
            average_blue += copy[height - 1 + i][j].rgbtBlue;
        }
    }
    image[height - 1][0].rgbtRed = (int) round(average_red / 4.0);
    image[height - 1][0].rgbtGreen = (int) round(average_green / 4.0);
    image[height - 1][0].rgbtBlue = (int) round(average_blue / 4.0);

    // left-bottom corner (height - 1, width - 1)
    average_red = 0, average_green = 0, average_blue = 0;
    //pattern for row -1 -> 0
    for (int i = -1; i < 1; i++)
    {
        //pattern for col -1 -> 0
        for (int j = -1; j < 1; j++)
        {
            average_red += copy[height - 1 + i][width - 1 + j].rgbtRed;
            average_green += copy[height - 1 + i][width - 1 + j].rgbtGreen;
            average_blue += copy[height - 1 + i][width - 1 + j].rgbtBlue;
        }
    }
    image[height - 1][width - 1].rgbtRed = (int) round(average_red / 4.0);
    image[height - 1][width - 1].rgbtGreen = (int) round(average_green / 4.0);
    image[height - 1][width - 1].rgbtBlue = (int) round(average_blue / 4.0);

    //upper-row
    // -**-
    // ----
    // ----
    // ----
    //start from (0, 1) to (0, width -2)
    for (int m = 1; m < width - 1; m++)
    {
        average_red = 0, average_green = 0, average_blue = 0;
        //pattern for row 0 -> 1
        for (int i = 0; i < 2; i++)
        {
            //pattern for col -1 -> 1
            for (int j = -1; j < 2; j++)
            {
                average_red += copy[0 + i][m + j].rgbtRed;
                average_green += copy[0 + i][m + j].rgbtGreen;
                average_blue += copy[0 + i][m + j].rgbtBlue;
            }
        }
        image[0][m].rgbtRed = (int) round(average_red / 6.0);
        image[0][m].rgbtGreen = (int) round(average_green / 6.0);
        image[0][m].rgbtBlue = (int) round(average_blue / 6.0);
    }

    //lower-row
    // ----
    // ----
    // ----
    // -**-
    //start from (height - 1, 1) to (height - 1, width -2)
    for (int m = 1; m < width - 1; m++)
    {
        average_red = 0, average_green = 0, average_blue = 0;
        //pattern for row -1 -> 0
        for (int i = -1; i < 1; i++)
        {
            //pattern for col -1 -> 1
            for (int j = -1; j < 2; j++)
            {
                average_red += copy[height - 1 + i][m + j].rgbtRed;
                average_green += copy[height - 1 + i][m + j].rgbtGreen;
                average_blue += copy[height - 1 + i][m + j].rgbtBlue;
            }
        }
        image[height - 1][m].rgbtRed = (int) round(average_red / 6.0);
        image[height - 1][m].rgbtGreen = (int) round(average_green / 6.0);
        image[height - 1][m].rgbtBlue = (int) round(average_blue / 6.0);
    }

    //left-col
    // ----
    // *---
    // *---
    // ----
    //start from (1, 0) to (height - 2, 0)
    for (int m = 1; m < height - 1; m++)
    {
        average_red = 0, average_green = 0, average_blue = 0;
        //pattern for row -1 -> 1
        for (int i = -1; i < 2; i++)
        {
            //pattern for col 0 -> 1
            for (int j = 0; j < 2; j++)
            {
                average_red += copy[m + i][j].rgbtRed;
                average_green += copy[m + i][j].rgbtGreen;
                average_blue += copy[m + i][j].rgbtBlue;
            }
        }
        image[m][0].rgbtRed = (int) round(average_red / 6.0);
        image[m][0].rgbtGreen = (int) round(average_green / 6.0);
        image[m][0].rgbtBlue = (int) round(average_blue / 6.0);
    }

    //right-col
    // ----
    // ---*
    // ---*
    // ----
    //start from (1, width - 1) to (height - 2, width - 1)
    for (int m = 1; m < height - 1; m++)
    {
        average_red = 0, average_green = 0, average_blue = 0;
        //pattern for row -1 -> 1
        for (int i = -1; i < 2; i++)
        {
            //pattern for col -1 -> 0
            for (int j = -1; j < 1; j++)
            {
                average_red += copy[m + i][width - 1 + j].rgbtRed;
                average_green += copy[m + i][width - 1 + j].rgbtGreen;
                average_blue += copy[m + i][width - 1 + j].rgbtBlue;

            }
        }
        image[m][width - 1].rgbtRed = (int) round(average_red / 6.0);
        image[m][width - 1].rgbtGreen = (int) round(average_green / 6.0);
        image[m][width - 1].rgbtBlue = (int) round(average_blue / 6.0);
    }

    return;
}
