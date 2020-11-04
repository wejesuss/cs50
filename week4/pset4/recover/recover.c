#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE;
typedef unsigned char bool;

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage %s image\n", argv[0]);
        return 1;
    }

    char *forensic = argv[1];

    FILE *forensic_img = fopen(forensic, "r");
    if (forensic_img == NULL)
    {
        printf("Could not open %s.\n", forensic);
        return 1;
    }

    BYTE *bytes = malloc(sizeof(BYTE) * 512);
    if (bytes == NULL)
    {
        fclose(forensic_img);
        printf("Insufficient memory\n");
        return 1;
    }

    int images = 0;
    char *filename = malloc(sizeof(char) * 8);
    sprintf(filename, "%03i.jpg", images);

    FILE *file = fopen(filename, "w");
    if (file == NULL)
    {
        fclose(forensic_img);
        free(bytes);
        printf("Could not open %s.\n", filename);
        return 1;
    }

    while (fread(bytes, 512, 1, forensic_img))
    {
        bool three_bytes = bytes[0] == 0xff && bytes[1] == 0xd8 && bytes[2] == 0xff;
        bool fourth_byte = (bytes[3] & 0xf0) == 0xe0;

        if (three_bytes && fourth_byte)
        {
            if (images != 0)
            {
                fclose(file);
                sprintf(filename, "%03i.jpg", images);
                file = fopen(filename, "w");
                if (file == NULL)
                {
                    fclose(forensic_img);
                    free(bytes);
                    free(filename);
                    printf("Could not open %s.\n", filename);
                    return 1;
                }
            }

            fwrite(bytes, 512, 1, file);
            images++;
        }
        else
        {
            if (images != 0)
            {
                fwrite(bytes, 512, 1, file);
            }
        }
    }

    fclose(forensic_img);
    fclose(file);
    free(bytes);
    free(filename);

    return 0;
}