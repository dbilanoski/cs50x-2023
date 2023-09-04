#include "helpers.h"

void colorize(int height, int width, RGBTRIPLE image[height][width])
{
    // Change all black pixels to a color of your choosing
    // So pixel by pixel, each row of width
    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            // Colors are specified with RGBTRIPPLE struct, each color as a hexadecimal value between 0-255
            /*
            typedef struct
            {
            BYTE rgbtBlue;
            BYTE rgbtGreen;
            BYTE rgbtRed;
            }
            RGBTRIPLE;
            */

            // If black (all three rgb components are 0), change to LIME (rgb(0,255,0) = 0x00FF00)
            if (image[i][j].rgbtBlue == 0x00 && image[i][j].rgbtGreen == 0x00 && image[i][j].rgbtBlue == 0x00)
            {
                image[i][j].rgbtGreen = 0xff;
            }
        }
    }
}
