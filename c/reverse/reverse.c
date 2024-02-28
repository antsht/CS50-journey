#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "wav.h"

int check_format(WAVHEADER header);
int get_block_size(WAVHEADER header);

const int HEADER_SIZE = 44;

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        printf("Usage: ./reverse input.wav output.wav\n");
        return 1;
    }

    // Open input file for reading
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    // Read header
    WAVHEADER header;
    fread(&header, HEADER_SIZE, 1, input);

    // Use check_format to ensure WAV format
    if (check_format(header) != 0)
    {
        printf("Invalid file format.\n");
        fclose(input);
        return 1;
    }

    // Open output file for writing
    FILE *output = fopen(argv[2], "w");
    if (output == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    // Write header to file
    fwrite(&header, HEADER_SIZE, 1, output);

    // Use get_block_size to calculate size of block
    int block_size = get_block_size(header);
    long data_size = header.subchunk2Size;
    // printf("\nInput position: %ld \nOutput position: %ld \nData size: %ld \nBlock size: %d\n", ftell(input), ftell(output),
    // data_size, block_size);
    //  Write reversed audio to file
    uint8_t *buf = (uint8_t *) malloc(block_size);
    fseek(input, 0, SEEK_END);
    for (long i = 1, end = data_size / block_size; i <= end; ++i)yas
    {
        fseek(input, -block_size, SEEK_CUR);
        fread(buf, block_size, 1, input);
        fwrite(buf, block_size, 1, output);
        fseek(input, -block_size, SEEK_CUR);
    }

    free(buf);
    fclose(input);
    fclose(output);
}

int check_format(WAVHEADER header)
{
    if (!(header.format[0] = 'W') || !(header.format[1] = 'A') || !(header.format[2] = 'W') || !(header.format[3] = 'E') ||
        (header.audioFormat != 1))
    {
        return 1;
    }
    return 0;
}

int get_block_size(WAVHEADER header)
{
    return header.numChannels * header.bitsPerSample / 8;
}
