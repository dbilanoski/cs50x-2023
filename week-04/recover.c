#include <stdio.h>
#include <stdlib.h>

const int BLOCK_SIZE = 512;

int main(int argc, char *argv[])
{
    // Check cli arguments
    if (argc != 2)
    {
        printf("Usage: ./recover your-file.raw\n");
        return 1;
    }

    // Open given raw file via cli. If unable to read from it, exit with error
    FILE *file = fopen(argv[1], "r");
    if (file == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    // Loop over 512 block size then check each if the starting bytes fit the jpeg pattern
    // If yes, update start flag, create three digit increment name and placeholder file, keep looping
    // On next new image update stop flag
    // Save image, close image, keep looping
    // When done free allocated memory

    // Buffer
    // After some googling figured that I need unsigned char to overcome default 255 size of char
    unsigned char *buffer = malloc(BLOCK_SIZE);
    // New file to be saved
    FILE *new_image = NULL;
    // Counter
    int counter = 0;
    // Flags for delimiting images
    int start_image = 0;
    int stop_image = 0;

    while (fread(buffer, 1, BLOCK_SIZE, file) == BLOCK_SIZE)
    {
        // First three bytes are 0xff 0xd8 0xff
        // Fourth is from 0xe0 to 0xef, can be written as buffer[3] & 0xf0) == 0xe0
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            // New image found - set the flags
            if ((start_image == 1 && stop_image == 1) || (start_image == 1 && counter == 1))
            {
                // I already wrote to the file. Close file and reset flag
                fclose(new_image);
                stop_image = 0;
            }

            if (start_image == 1)
            {
                // End of the image found
                stop_image = 1;
            }

            if (start_image == 0)
            {
                // Start of the image found
                start_image = 1;
            }

            // Create new filename based on current count
            // Three digit sintax: %03i
            char filename[10];
            sprintf(filename, "%03i.jpg", counter);
            // Open new placeholder file where we are to save this image
            new_image = fopen(filename, "w");
            // Increment
            counter ++;
        }

        // In case I found the end of the image (first image case also), write to the file
        if ((stop_image == 1 && start_image == 1) || (start_image == 1 && counter == 1))
        {
            fwrite(buffer, BLOCK_SIZE, 1, new_image);
        }
    }

    // Outro
    fclose(file);
    fclose(new_image);
    free(buffer);
    return 0;

}