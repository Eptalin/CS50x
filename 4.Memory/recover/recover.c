#include <cs50.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    // Confirm user gave exactly 1 argument
    if (argc != 2)
    {
        printf("Usage: ./recover filename\n");
        return 1;
    }

    // Initialise output file pointer, file counter, and filename array
    FILE *jpeg = NULL;
    int jpeg_n = 0;
    char filename[8];

    // Create buffer
    int block_size = 512;
    uint8_t buffer[block_size];

    // Open input file to read
    FILE *card = fopen(argv[1], "r");

    // While there's still data left on the memory card
    while (fread(buffer, 1, block_size, card) == block_size)
    {
        // Create .jpeg's from the data
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff &&
                 (buffer[3] & 0xf0) == 0xe0)
        {
            // If not first image, close previous file
            if (jpeg_n > 0)
            {
                fclose(jpeg);
            }

            // Create and open a new numbered jpeg file and increment counter
            sprintf(filename, "%03i.jpg", jpeg_n);
            jpeg = fopen(filename, "w");
            jpeg_n += 1;
        }

        // Write data to open jpeg file
        if (jpeg != NULL)
        {
            fwrite(buffer, 1, block_size, jpeg);
        }
    }
    if (jpeg != NULL)
    {
        fclose(jpeg);
    }
    fclose(card);
}
