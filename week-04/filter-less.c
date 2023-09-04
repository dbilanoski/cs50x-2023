#include "helpers.h"
#include <math.h>

/*
RGPTRIPLE struct
    BYTE  rgbtBlue;
    BYTE  rgbtGreen;
    BYTE  rgbtRed;

*/

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // Grey means put red, green and blue to same value
    // To determine appropriate brightness, we take average of rgb values (r+g+b/3)

    float average_color;
    // For each row do pixel by pixel > calculate average > set new pixel
    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            average_color = (image[j][i].rgbtBlue + image[j][i].rgbtGreen + image[j][i].rgbtRed) / 3.0;
            // Set new values
            image[j][i].rgbtBlue = round(average_color);
            image[j][i].rgbtGreen = round(average_color);
            image[j][i].rgbtRed = round(average_color);
        }
    }

    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    /*
    Provided algorithm for calculating sephia:

        sepiaRed = .393 * originalRed + .769 * originalGreen + .189 * originalBlue
        sepiaGreen = .349 * originalRed + .686 * originalGreen + .168 * originalBlue
        sepiaBlue = .272 * originalRed + .534 * originalGreen + .131 * originalBlue
    */

    // For each row do pixel by pixel > calculate new value based on provided alogrithm and round to nearest int >
    // > if bigger then 255 set to 255 > set new pixel

    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {

            // Red
            int sepiaRed = round(0.393 * image[j][i].rgbtRed + 0.769 * image[j][i].rgbtGreen + 0.189 * image[j][i].rgbtBlue);
            // If bigger than 255, set to 255
            if (sepiaRed > 255)
            {
                sepiaRed = 255;
            }

            // Green
            int sepiaGreen = round(0.349 * image[j][i].rgbtRed + 0.686 * image[j][i].rgbtGreen + 0.168 * image[j][i].rgbtBlue);
            // If bigger than 255, set to 255
            if (sepiaGreen > 255)
            {
                sepiaGreen = 255;
            }

            // Blue
            int sepiaBlue = round(0.272 * image[j][i].rgbtRed + 0.534 * image[j][i].rgbtGreen + 0.131 * image[j][i].rgbtBlue);
            // If bigger than 255, set to 255
            if (sepiaBlue > 255)
            {
                sepiaBlue = 255;
            }

            // Set new values
            image[j][i].rgbtBlue = sepiaBlue;
            image[j][i].rgbtGreen = sepiaGreen;
            image[j][i].rgbtRed = sepiaRed;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // Mirror image, I swap each row's frist to last pixel
    RGBTRIPLE current_row;
    // If I let it whole with, I get same image so swaping needs to stop at middle
    for (int i = 0; i < width - (width / 2); i++)
    {
        for (int j = 0; j < height; j++)
        {

            current_row = image[j][i];
            image[j][i] = image[j][width - i - 1];
            image[j][width - i - 1] = current_row;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Box blur, takes average of all neighbouring pixels in a 3x3 grid
    // In case of pixels on the edge of the image, those not available we just skip

    // Specification says create copy of the image and work with it to avoid issues with bluring neighboring pixels
    RGBTRIPLE copy[height][width];

    // Populate copy with data from image
    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            copy[j][i] = image[j][i];
        }
    }

    // For each row pixel by pixel - need counter and sum vars
    // Reset sum and count vars to 0
    // Check if pixel is in corners
    // Check if pixel is on edges
    // Check if pixel is in the middle
    // Add surrounding values to temp vars
    // Calculate averages, round values, update new image

    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {

            float counter = 0;
            float blue_sum = 0;
            float green_sum = 0;
            float red_sum = 0;

            // Corners: Top Left
            if (j - 1 >= 0 && i >= 0)
            {
                blue_sum += copy[j - 1][i].rgbtBlue;
                green_sum += copy[j - 1][i].rgbtGreen;
                red_sum += copy[j - 1][i].rgbtRed;
                counter++;
            }
            // Corners: Top Right
            if (j - 1 >= 0 && i - 1 >= 0)
            {
                blue_sum += copy[j - 1][i - 1].rgbtBlue;
                green_sum += copy[j - 1][i - 1].rgbtGreen;
                red_sum += copy[j - 1][i - 1].rgbtRed;
                counter++;
            }

            // Corners: Bottom Left
            if (j < height && i - 1 >= 0)
            {
                blue_sum += copy[j][i - 1].rgbtBlue;
                green_sum += copy[j][i - 1].rgbtGreen;
                red_sum += copy[j][i - 1].rgbtRed;
                counter++;
            }

            // Corners: Bottom Right
            if (j < height && i >= 0)
            {
                blue_sum += copy[j][i].rgbtBlue;
                green_sum += copy[j][i].rgbtGreen;
                red_sum += copy[j][i].rgbtRed;
                counter++;
            }

            // Borders: Top
            if (j - 1 >= 0 && i + 1 < width && i + 1 >= 0)
            {
                blue_sum += copy[j - 1][i + 1].rgbtBlue;
                green_sum += copy[j - 1][i + 1].rgbtGreen;
                red_sum += copy[j - 1][i + 1].rgbtRed;
                counter++;
            }

            // Borders: Bottom
            if (j < height && i + 1 >= 0 && i + 1 < width)
            {
                blue_sum += copy[j][i + 1].rgbtBlue;
                green_sum += copy[j][i + 1].rgbtGreen;
                red_sum += copy[j][i + 1].rgbtRed;
                counter++;
            }

            // Borders: Left
            if (j + 1 < height && j + 1 >= 0 && i >= 0)
            {
                blue_sum += copy[j + 1][i].rgbtBlue;
                green_sum += copy[j + 1][i].rgbtGreen;
                red_sum += copy[j + 1][i].rgbtRed;
                counter++;
            }

            // Borders: Right
            if (j + 1 < height && j + 1 >= 0 && i - 1 >= 0)
            {
                blue_sum += copy[j + 1][i - 1].rgbtBlue;
                green_sum += copy[j + 1][i - 1].rgbtGreen;
                red_sum += copy[j + 1][i - 1].rgbtRed;
                counter++;
            }

            // Middle case
            // Neigbors are less than height and width
            if (j + 1 < height && i + 1 < width)
            {
                blue_sum += copy[j + 1][i + 1].rgbtBlue;
                green_sum += copy[j + 1][i + 1].rgbtGreen;
                red_sum += copy[j + 1][i + 1].rgbtRed;
                counter++;
            }

            // Calculate averages
            int blue_avg = round(blue_sum / counter);
            // If value bigger than 255, set 255
            if (blue_avg > 255)
            {
                blue_avg = 255;
            }

            int green_avg = round(green_sum / counter);
            // If value bigger than 255, set 255
            if (green_avg > 255)
            {
                green_avg = 255;
            }

            int red_avg = round(red_sum / counter);
            // If value bigger than 255, set 255
            if (red_avg > 255)
            {
                red_avg = 255;
            }

            // Set new values to original image
            image[j][i].rgbtBlue = blue_avg;
            image[j][i].rgbtGreen = green_avg;
            image[j][i].rgbtRed = red_avg;
        }
    }

    return;
}