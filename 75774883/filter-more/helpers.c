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
            image[i][j].rgbtBlue = (int)average;                                                               // set it all the same
            image[i][j].rgbtGreen = (int)average;
            image[i][j].rgbtRed = (int)average;
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
    // copy a picture to
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
            image[i][j].rgbtRed = (int)round(average_red / 9.0);
            image[i][j].rgbtGreen = (int)round(average_green / 9.0);
            image[i][j].rgbtBlue = (int)round(average_blue / 9.0);
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
    image[0][0].rgbtRed = (int)round(average_red / 4.0);
    image[0][0].rgbtGreen = (int)round(average_green / 4.0);
    image[0][0].rgbtBlue = (int)round(average_blue / 4.0);

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
    image[0][width - 1].rgbtRed = (int)round(average_red / 4.0);
    image[0][width - 1].rgbtGreen = (int)round(average_green / 4.0);
    image[0][width - 1].rgbtBlue = (int)round(average_blue / 4.0);

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
    image[height - 1][0].rgbtRed = (int)round(average_red / 4.0);
    image[height - 1][0].rgbtGreen = (int)round(average_green / 4.0);
    image[height - 1][0].rgbtBlue = (int)round(average_blue / 4.0);

    // left-bottom corner (height - 1, width - 1)
    average_red = 0, average_green = 0, average_blue = 0;
    // pattern for row -1 -> 0
    for (int i = -1; i < 1; i++)
    {
        // pattern for col -1 -> 0
        for (int j = -1; j < 1; j++)
        {
            average_red += copy[height - 1 + i][width - 1 + j].rgbtRed;
            average_green += copy[height - 1 + i][width - 1 + j].rgbtGreen;
            average_blue += copy[height - 1 + i][width - 1 + j].rgbtBlue;
        }
    }
    image[height - 1][width - 1].rgbtRed = (int)round(average_red / 4.0);
    image[height - 1][width - 1].rgbtGreen = (int)round(average_green / 4.0);
    image[height - 1][width - 1].rgbtBlue = (int)round(average_blue / 4.0);

    // upper-row
    //  -**-
    //  ----
    //  ----
    //  ----
    // start from (0, 1) to (0, width -2)
    for (int m = 1; m < width - 1; m++)
    {
        average_red = 0, average_green = 0, average_blue = 0;
        // pattern for row 0 -> 1
        for (int i = 0; i < 2; i++)
        {
            // pattern for col -1 -> 1
            for (int j = -1; j < 2; j++)
            {
                average_red += copy[0 + i][m + j].rgbtRed;
                average_green += copy[0 + i][m + j].rgbtGreen;
                average_blue += copy[0 + i][m + j].rgbtBlue;
            }
        }
        image[0][m].rgbtRed = (int)round(average_red / 6.0);
        image[0][m].rgbtGreen = (int)round(average_green / 6.0);
        image[0][m].rgbtBlue = (int)round(average_blue / 6.0);
    }

    // lower-row
    //  ----
    //  ----
    //  ----
    //  -**-
    // start from (height - 1, 1) to (height - 1, width -2)
    for (int m = 1; m < width - 1; m++)
    {
        average_red = 0, average_green = 0, average_blue = 0;
        // pattern for row -1 -> 0
        for (int i = -1; i < 1; i++)
        {
            // pattern for col -1 -> 1
            for (int j = -1; j < 2; j++)
            {
                average_red += copy[height - 1 + i][m + j].rgbtRed;
                average_green += copy[height - 1 + i][m + j].rgbtGreen;
                average_blue += copy[height - 1 + i][m + j].rgbtBlue;
            }
        }
        image[height - 1][m].rgbtRed = (int)round(average_red / 6.0);
        image[height - 1][m].rgbtGreen = (int)round(average_green / 6.0);
        image[height - 1][m].rgbtBlue = (int)round(average_blue / 6.0);
    }

    // left-col
    //  ----
    //  *---
    //  *---
    //  ----
    // start from (1, 0) to (height - 2, 0)
    for (int m = 1; m < height - 1; m++)
    {
        average_red = 0, average_green = 0, average_blue = 0;
        // pattern for row -1 -> 1
        for (int i = -1; i < 2; i++)
        {
            // pattern for col 0 -> 1
            for (int j = 0; j < 2; j++)
            {
                average_red += copy[m + i][j].rgbtRed;
                average_green += copy[m + i][j].rgbtGreen;
                average_blue += copy[m + i][j].rgbtBlue;
            }
        }
        image[m][0].rgbtRed = (int)round(average_red / 6.0);
        image[m][0].rgbtGreen = (int)round(average_green / 6.0);
        image[m][0].rgbtBlue = (int)round(average_blue / 6.0);
    }

    // right-col
    //  ----
    //  ---*
    //  ---*
    //  ----
    // start from (1, width - 1) to (height - 2, width - 1)
    for (int m = 1; m < height - 1; m++)
    {
        average_red = 0, average_green = 0, average_blue = 0;
        // pattern for row -1 -> 1
        for (int i = -1; i < 2; i++)
        {
            // pattern for col -1 -> 0
            for (int j = -1; j < 1; j++)
            {
                average_red += copy[m + i][width - 1 + j].rgbtRed;
                average_green += copy[m + i][width - 1 + j].rgbtGreen;
                average_blue += copy[m + i][width - 1 + j].rgbtBlue;
            }
        }
        image[m][width - 1].rgbtRed = (int)round(average_red / 6.0);
        image[m][width - 1].rgbtGreen = (int)round(average_green / 6.0);
        image[m][width - 1].rgbtBlue = (int)round(average_blue / 6.0);
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    // copy a picture to
    RGBTRIPLE copy[height][width];
    for (int i = 0; i < height; i++) // control height (row)
    {
        for (int j = 0; j < width; j++) // control width (column)
        {
            copy[i][j] = image[i][j]; // make a copy byte
        }
    }

    const int GX[3][2] = {{-1, 1}, {-2, 2}, {-1, 1}};
    const int GY[2][3] = {{-1, -2, -1}, {1, 2, 1}};

    // do the inner square
    // ----
    // -**-
    // -**-
    // ----
    // control for row
    for (int i = 1; i < height - 1; i++)
    {
        // control for col
        for (int j = 1; j < width - 1; j++)
        {
            double ans_red = 0, ans_green = 0, ans_blue = 0;
            // loop for horizontal
            //  *-*-
            //  *0*-
            //  *-*-
            //  ----
            //  example for (1,1)
            double sum_red = 0, sum_green = 0, sum_blue = 0;
            for (int row = 0; row < 3; row++)
            {
                for (int col = 0; col < 2; col++)
                {
                    // pattern
                    // row -1 -> 0 -> 1 but for loop pattern is 0 1 2 thus minus 1 in row
                    // col -1 -> 1 but for loop pattern is 0 1 thus col * 2 - 1
                    sum_red += GX[row][col] * copy[i + (row - 1)][j + (2 * col - 1)].rgbtRed;
                    sum_green += GX[row][col] * copy[i + (row - 1)][j + (2 * col - 1)].rgbtGreen;
                    sum_blue += GX[row][col] * copy[i + (row - 1)][j + (2 * col - 1)].rgbtBlue;
                }
            }
            ans_red += sum_red * sum_red;
            ans_green += sum_green * sum_green;
            ans_blue += sum_blue * sum_blue;

            // loop for vertical
            //  ***-
            //  -0--
            //  ***-
            //  ----
            //  example for (1,1)
            sum_red = 0, sum_green = 0, sum_blue = 0;
            for (int row = 0; row < 2; row++)
            {
                for (int col = 0; col < 3; col++)
                {
                    // pattern
                    // col -1 -> 0 -> 1 but for loop pattern is 0 1 2 thus minus 1 in col
                    // row -1 -> 1 but for loop pattern is 0 1 thus row * 2 - 1
                    sum_red += GY[row][col] * copy[i + (2 * row - 1)][j + (col - 1)].rgbtRed;
                    sum_green += GY[row][col] * copy[i + (2 * row - 1)][j + (col - 1)].rgbtGreen;
                    sum_blue += GY[row][col] * copy[i + (2 * row - 1)][j + (col - 1)].rgbtBlue;
                }
            }
            ans_red += sum_red * sum_red;
            ans_green += sum_green * sum_green;
            ans_blue += sum_blue * sum_blue;

            image[i][j].rgbtRed = (int)round(sqrt(ans_red));
            image[i][j].rgbtRed = image[i][j].rgbtRed > 255 ? 255 : image[i][j].rgbtRed;

            image[i][j].rgbtGreen = (int)round(sqrt(ans_green));
            image[i][j].rgbtGreen = image[i][j].rgbtGreen > 255 ? 255 : image[i][j].rgbtGreen;

            image[i][j].rgbtBlue = (int)round(sqrt(ans_blue));
            image[i][j].rgbtBlue = image[i][j].rgbtBlue > 255 ? 255 : image[i][j].rgbtBlue;
        }
    }

    // top-left corner
    //  0*--
    //  **--
    //  ----
    //  ----
    //  4 adjuntion cell (0, 0)
    double ans_red = 0, ans_green = 0, ans_blue = 0;

    // Get Gx
    double sum_red = 0, sum_green = 0, sum_blue = 0;
    for (int i = 0; i < 2; i++)
    {
        sum_red += GX[i + 1][1] * copy[i][1].rgbtRed;
        sum_green += GX[i + 1][1] * copy[i][1].rgbtGreen;
        sum_blue += GX[i + 1][1] * copy[i][1].rgbtBlue;
    }
    ans_red += sum_red * sum_red;
    ans_green += sum_green * sum_green;
    ans_blue += sum_blue * sum_blue;

    // Get Gy
    sum_red = 0, sum_green = 0, sum_blue = 0;
    for (int i = 0; i < 2; i++)
    {
        sum_red += GY[1][i + 1] * copy[1][i].rgbtRed;
        sum_green += GY[1][i + 1] * copy[1][i].rgbtGreen;
        sum_blue += GY[1][i + 1] * copy[1][i].rgbtBlue;
    }
    ans_red += sum_red * sum_red;
    ans_green += sum_green * sum_green;
    ans_blue += sum_blue * sum_blue;

    ans_red = round(sqrt(ans_red)) > 255 ? 255 : round(sqrt(ans_red));
    ans_green = round(sqrt(ans_green)) > 255 ? 255 : round(sqrt(ans_green));
    ans_blue = round(sqrt(ans_blue)) > 255 ? 255 : round(sqrt(ans_blue));

    image[0][0].rgbtRed = (int)ans_red;
    image[0][0].rgbtGreen = (int)ans_green;
    image[0][0].rgbtBlue = (int)ans_blue;

    // top-right corner
    //  -*0
    //  -**
    //  ----
    //  ----
    //  4 adjuntion cell (0, width - 1)
    ans_red = 0, ans_green = 0, ans_blue = 0;

    // Get Gx
    sum_red = 0, sum_green = 0, sum_blue = 0;
    for (int i = 0; i < 2; i++)
    {
        sum_red += GX[i + 1][0] * copy[i][width - 2].rgbtRed;
        sum_green += GX[i + 1][0] * copy[i][width - 2].rgbtGreen;
        sum_blue += GX[i + 1][0] * copy[i][width - 2].rgbtBlue;
    }
    ans_red += sum_red * sum_red;
    ans_green += sum_green * sum_green;
    ans_blue += sum_blue * sum_blue;

    // Get Gy
    sum_red = 0, sum_green = 0, sum_blue = 0;
    for (int i = 0; i < 2; i++)
    {
        sum_red += GY[1][i] * copy[1][width - 2 + i].rgbtRed;
        sum_green += GY[1][i] * copy[1][width - 2 + i].rgbtGreen;
        sum_blue += GY[1][i] * copy[1][width - 2 + i].rgbtBlue;
    }
    ans_red += sum_red * sum_red;
    ans_green += sum_green * sum_green;
    ans_blue += sum_blue * sum_blue;

    ans_red = round(sqrt(ans_red)) > 255 ? 255 : round(sqrt(ans_red));
    ans_green = round(sqrt(ans_green)) > 255 ? 255 : round(sqrt(ans_green));
    ans_blue = round(sqrt(ans_blue)) > 255 ? 255 : round(sqrt(ans_blue));

    image[0][width - 1].rgbtRed = (int)ans_red;
    image[0][width - 1].rgbtGreen = (int)ans_green;
    image[0][width - 1].rgbtBlue = (int)ans_blue;

    // bottom-right corner
    //  ----
    //  ----
    //  **--
    //  0*--
    //  4 adjuntion cell (height - 1, 0)
    ans_red = 0, ans_green = 0, ans_blue = 0;

    // Get Gx
    sum_red = 0, sum_green = 0, sum_blue = 0;
    for (int i = 0; i < 2; i++)
    {
        sum_red += GX[i][1] * copy[height - 2 + i][1].rgbtRed;
        sum_green += GX[i][1] * copy[height - 2 + i][1].rgbtGreen;
        sum_blue += GX[i][1] * copy[height - 2 + i][1].rgbtBlue;
    }
    ans_red += sum_red * sum_red;
    ans_green += sum_green * sum_green;
    ans_blue += sum_blue * sum_blue;

    // Get Gy
    sum_red = 0, sum_green = 0, sum_blue = 0;
    for (int i = 0; i < 2; i++)
    {
        sum_red += GY[0][i + 1] * copy[height - 2][i].rgbtRed;
        sum_green += GY[0][i + 1] * copy[height - 2][i].rgbtGreen;
        sum_blue += GY[0][i + 1] * copy[height - 2][i].rgbtBlue;
    }
    ans_red += sum_red * sum_red;
    ans_green += sum_green * sum_green;
    ans_blue += sum_blue * sum_blue;

    ans_red = round(sqrt(ans_red)) > 255 ? 255 : round(sqrt(ans_red));
    ans_green = round(sqrt(ans_green)) > 255 ? 255 : round(sqrt(ans_green));
    ans_blue = round(sqrt(ans_blue)) > 255 ? 255 : round(sqrt(ans_blue));

    image[height - 1][0].rgbtRed = (int)ans_red;
    image[height - 1][0].rgbtGreen = (int)ans_green;
    image[height - 1][0].rgbtBlue = (int)ans_blue;

    // bottom-right corner
    //  ----
    //  ----
    //  --**
    //  --*0
    //  4 adjuntion cell (height - 1, width - 1)
    ans_red = 0, ans_green = 0, ans_blue = 0;

    // Get Gx
    sum_red = 0, sum_green = 0, sum_blue = 0;
    for (int i = 0; i < 2; i++)
    {
        sum_red += GX[i][0] * copy[height - 2 + i][width - 2].rgbtRed;
        sum_green += GX[i][0] * copy[height - 2 + i][width - 2].rgbtGreen;
        sum_blue += GX[i][0] * copy[height - 2 + i][width - 2].rgbtBlue;
    }
    ans_red += sum_red * sum_red;
    ans_green += sum_green * sum_green;
    ans_blue += sum_blue * sum_blue;

    // Get Gy
    sum_red = 0, sum_green = 0, sum_blue = 0;
    for (int i = 0; i < 2; i++)
    {
        sum_red += GY[0][i] * copy[height - 2][width - 2 + i].rgbtRed;
        sum_green += GY[0][i] * copy[height - 2][width - 2 + i].rgbtGreen;
        sum_blue += GY[0][i] * copy[height - 2][width - 2 + i].rgbtBlue;
    }
    ans_red += sum_red * sum_red;
    ans_green += sum_green * sum_green;
    ans_blue += sum_blue * sum_blue;

    ans_red = round(sqrt(ans_red)) > 255 ? 255 : round(sqrt(ans_red));
    ans_green = round(sqrt(ans_green)) > 255 ? 255 : round(sqrt(ans_green));
    ans_blue = round(sqrt(ans_blue)) > 255 ? 255 : round(sqrt(ans_blue));

    image[height - 1][width - 1].rgbtRed = (int)ans_red;
    image[height - 1][width - 1].rgbtGreen = (int)ans_green;
    image[height - 1][width - 1].rgbtBlue = (int)ans_blue;

    // upper edge
    //  *0*-
    //  ***-
    //  ----
    //  ----
    //  5 adjuntion cell example: (1, 1)
    for (int m = 1; m < width - 1; m++)
    {
        ans_red = 0, ans_green = 0, ans_blue = 0;

        // Get Gx
        // *0*-
        // *-*-
        // ----
        // ----
        sum_red = 0, sum_green = 0, sum_blue = 0;
        for (int i = 0; i < 2; i++)
        {
            for (int j = 0; j < 2; j++)
            {
                sum_red += GX[i + 1][j] * copy[i][m + (2 * j - 1)].rgbtRed;
                sum_green += GX[i + 1][j] * copy[i][m + (2 * j - 1)].rgbtGreen;
                sum_blue += GX[i + 1][j] * copy[i][m + (2 * j - 1)].rgbtBlue;
            }
        }
        ans_red += sum_red * sum_red;
        ans_green += sum_green * sum_green;
        ans_blue += sum_blue * sum_blue;

        // Get Gy
        sum_red = 0, sum_green = 0, sum_blue = 0;
        for (int i = 0; i < 3; i++)
        {
            sum_red += GY[1][i] * copy[1][i + m - 1].rgbtRed;
            sum_green += GY[1][i] * copy[1][i + m - 1].rgbtGreen;
            sum_blue += GY[1][i] * copy[1][i + m - 1].rgbtBlue;
        }
        ans_red += sum_red * sum_red;
        ans_green += sum_green * sum_green;
        ans_blue += sum_blue * sum_blue;

        ans_red = round(sqrt(ans_red)) > 255 ? 255 : round(sqrt(ans_red));
        ans_green = round(sqrt(ans_green)) > 255 ? 255 : round(sqrt(ans_green));
        ans_blue = round(sqrt(ans_blue)) > 255 ? 255 : round(sqrt(ans_blue));

        image[0][m].rgbtRed = (int)ans_red;
        image[0][m].rgbtGreen = (int)ans_green;
        image[0][m].rgbtBlue = (int)ans_blue;
    }

    // bottom edge
    //  ----
    //  ----
    //  ***-
    //  *0*-
    //  5 adjuntion cell example: (1, 1)
    for (int m = 1; m < width - 1; m++)
    {
        ans_red = 0, ans_green = 0, ans_blue = 0;

        // Get Gx
        // ----
        // ----
        // *-*-
        // *0*-
        sum_red = 0, sum_green = 0, sum_blue = 0;
        for (int i = 0; i < 2; i++)
        {
            for (int j = 0; j < 2; j++)
            {
                sum_red += GX[i][j] * copy[height - 2 + i][m + (2 * j - 1)].rgbtRed;
                sum_green += GX[i][j] * copy[height - 2 + i][m + (2 * j - 1)].rgbtGreen;
                sum_blue += GX[i][j] * copy[height - 2 + i][m + (2 * j - 1)].rgbtBlue;
            }
        }
        ans_red += sum_red * sum_red;
        ans_green += sum_green * sum_green;
        ans_blue += sum_blue * sum_blue;

        // Get Gy
        // ----
        // ----
        // ***-
        // -0--
        sum_red = 0, sum_green = 0, sum_blue = 0;
        for (int i = 0; i < 3; i++)
        {
            sum_red += GY[0][i] * copy[height - 2][i + m - 1].rgbtRed;
            sum_green += GY[0][i] * copy[height - 2][i + m - 1].rgbtGreen;
            sum_blue += GY[0][i] * copy[height - 2][i + m - 1].rgbtBlue;
        }
        ans_red += sum_red * sum_red;
        ans_green += sum_green * sum_green;
        ans_blue += sum_blue * sum_blue;

        ans_red = round(sqrt(ans_red)) > 255 ? 255 : round(sqrt(ans_red));
        ans_green = round(sqrt(ans_green)) > 255 ? 255 : round(sqrt(ans_green));
        ans_blue = round(sqrt(ans_blue)) > 255 ? 255 : round(sqrt(ans_blue));

        image[height - 1][m].rgbtRed = (int)ans_red;
        image[height - 1][m].rgbtGreen = (int)ans_green;
        image[height - 1][m].rgbtBlue = (int)ans_blue;
    }

    // left edge
    //  **--
    //  0*--
    //  **--
    //  ----
    //  5 adjuntion cell example: (1, 1)
    for (int m = 1; m < height - 1; m++)
    {
        ans_red = 0, ans_green = 0, ans_blue = 0;

        // Get Gx
        // -*--     -*
        // -*--     -*
        // -*--     -*
        // ----
        sum_red = 0, sum_green = 0, sum_blue = 0;
        for (int i = 0; i < 3; i++)
        {
            sum_red += GX[i][1] * copy[m - 1 + i][1].rgbtRed;
            sum_green += GX[i][1] * copy[m - 1 + i][1].rgbtGreen;
            sum_blue += GX[i][1] * copy[m - 1 + i][1].rgbtBlue;
        }
        ans_red += sum_red * sum_red;
        ans_green += sum_green * sum_green;
        ans_blue += sum_blue * sum_blue;

        // Get Gy
        // -**-
        // ----
        // -**-
        // ----
        sum_red = 0, sum_green = 0, sum_blue = 0;
        for (int i = 0; i < 2; i++)
        {
            for (int j = 0; j < 2; j++)
            {
                sum_red += GY[i][j + 1] * copy[m + (i * 2 - 1)][j].rgbtRed;
                sum_green += GY[i][j + 1] * copy[m + (i * 2 - 1)][j].rgbtGreen;
                sum_blue += GY[i][j + 1] * copy[m + (i * 2 - 1)][j].rgbtBlue;
            }
        }
        ans_red += sum_red * sum_red;
        ans_green += sum_green * sum_green;
        ans_blue += sum_blue * sum_blue;

        ans_red = round(sqrt(ans_red)) > 255 ? 255 : round(sqrt(ans_red));
        ans_green = round(sqrt(ans_green)) > 255 ? 255 : round(sqrt(ans_green));
        ans_blue = round(sqrt(ans_blue)) > 255 ? 255 : round(sqrt(ans_blue));

        image[m][0].rgbtRed = (int)ans_red;
        image[m][0].rgbtGreen = (int)ans_green;
        image[m][0].rgbtBlue = (int)ans_blue;
    }

    // right edge
    //  --*-
    //  --*0
    //  --*-
    //  ----
    //  5 adjuntion cell example: (1, 1)
    for (int m = 1; m < height - 1; m++)
    {
        ans_red = 0, ans_green = 0, ans_blue = 0;

        // Get Gx
        // --*-     *-
        // --*-     *-
        // --*-     *-
        // ----
        sum_red = 0, sum_green = 0, sum_blue = 0;
        for (int i = 0; i < 3; i++)
        {
            sum_red += GX[i][0] * copy[m - 1 + i][width - 2].rgbtRed;
            sum_green += GX[i][0] * copy[m - 1 + i][width - 2].rgbtGreen;
            sum_blue += GX[i][0] * copy[m - 1 + i][width - 2].rgbtBlue;
        }
        ans_red += sum_red * sum_red;
        ans_green += sum_green * sum_green;
        ans_blue += sum_blue * sum_blue;

        // Get Gy
        // --*- *-
        // ---- *-
        // --*-
        // ----
        sum_red = 0, sum_green = 0, sum_blue = 0;
        for (int i = 0; i < 2; i++)
        {
            for (int j = 0; j < 2; j++)
            {
                sum_red += GY[i][j] * copy[m + (i * 2 - 1)][width - 2 + j].rgbtRed;
                sum_green += GY[i][j] * copy[m + (i * 2 - 1)][width - 2 + j].rgbtGreen;
                sum_blue += GY[i][j] * copy[m + (i * 2 - 1)][width - 2 + j].rgbtBlue;
            }
        }
        ans_red += sum_red * sum_red;
        ans_green += sum_green * sum_green;
        ans_blue += sum_blue * sum_blue;

        ans_red = round(sqrt(ans_red)) > 255 ? 255 : round(sqrt(ans_red));
        ans_green = round(sqrt(ans_green)) > 255 ? 255 : round(sqrt(ans_green));
        ans_blue = round(sqrt(ans_blue)) > 255 ? 255 : round(sqrt(ans_blue));

        image[m][height - 1].rgbtRed = (int)ans_red;
        image[m][height - 1].rgbtGreen = (int)ans_green;
        image[m][height - 1].rgbtBlue = (int)ans_blue;
    }


    return;
}
