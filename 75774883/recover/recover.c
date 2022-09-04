#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>


typedef uint8_t BYTE;
bool is_jpeg(BYTE *buffer);
const int BLOCK_SIZE = 512;


int main(int argc, char *argv[])
{
    //check if user give input
    if (argc != 2)
    {
        printf("Usage: ./recover IMAGE\n");
        return 1;
    }

    //read file
    FILE *input = fopen("card.raw", "r");

    //check if file exist
    if (input == NULL)
    {
        printf("File doesn't exsit\n");
        return 1;
    }




    BYTE buffer[BLOCK_SIZE];
    int count = 0;
    char filename[8];
    FILE *output = NULL;

    while (fread(buffer, 1, BLOCK_SIZE, input) == BLOCK_SIZE)
    {
        if (is_jpeg(buffer))
        {
            if (output != NULL) //if it's jpg header and openning -> close it
            {
                fclose(output);
            }
            sprintf(filename, "%03i.jpg", count); //then create a new file
            output = fopen(filename, "w");
            count++;
        }
        if (output != NULL) //if the output file is created write down data to the file
        {
            fwrite(buffer, sizeof(buffer), 1, output);
        }
    }

    fclose(output);
    fclose(input);
}


bool is_jpeg(BYTE *buffer)
{
    //check if the first is 0xff
    if (buffer[0] != 0xff)
    {
        return false;
    }
    //check if the first is 0xd8
    if (buffer[1] != 0xd8)
    {
        return false;
    }
    //check if the first is 0xff
    if (buffer[2] != 0xff)
    {
        return false;
    }
    //check if the first is 0xe..
    if ((buffer[3] & 0xf0) != 0xe0)
    {
        return false;
    }

    return true;
}

