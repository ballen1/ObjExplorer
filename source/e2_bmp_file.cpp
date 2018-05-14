#include "e2_bmp_file.h"

#include <stdio.h>

bool
load_bmp_file(const char* file_path, e2_bmp_file& file)
{
    FILE* bmp_file = fopen(file_path, "rb");

    if (!bmp_file)
    {
        printf("Bmp file not found\n");
        return false;
    }

    long bmp_file_size;
    char* bmp_file_buffer;
   
    fseek(bmp_file, 0, SEEK_END);
    bmp_file_size = ftell(bmp_file);
    fseek(bmp_file, 0, SEEK_SET);
    
    bmp_file_buffer = new char[bmp_file_size];
    fread(bmp_file_buffer, 1, bmp_file_size, bmp_file);

    file.file_header.type[0] = bmp_file_buffer[0];
    file.file_header.type[1] = bmp_file_buffer[1];
    file.file_header.file_size = *((uint32_t*)&bmp_file_buffer[2]);
    file.file_header.reserved1 = *((uint16_t*)&bmp_file_buffer[6]);
    file.file_header.reserved2 = *((uint16_t*)&bmp_file_buffer[8]);
    file.file_header.offset_bits = *((uint32_t*)&bmp_file_buffer[10]);

    file.image_header.header_size = *((uint32_t*)&bmp_file_buffer[14]);
    file.image_header.image_width = *((uint32_t*)&bmp_file_buffer[18]);
    file.image_header.image_height = *((uint32_t*)&bmp_file_buffer[22]);
    file.image_header.planes = *((uint16_t*)&bmp_file_buffer[26]);
    file.image_header.bit_count = *((uint16_t*)&bmp_file_buffer[28]);

    if (file.image_header.bit_count == 24 || file.image_header.bit_count == 32)
    {
        size_t pixel_count = file.image_header.image_width * file.image_header.image_height;
        size_t pixel_data_count = pixel_count * 4;
        file.pixel_data = new uint8_t[pixel_data_count];
        size_t offset = file.file_header.offset_bits;

        int p = 0;
        for (int row = file.image_header.image_height - 1; row >= 0; row--)
        {
            for (int col = 0; col < file.image_header.image_width; col++)
            {
                int index = ((row * file.image_header.image_width) + col) * 4;
                file.pixel_data[(p * 4) + 2] = bmp_file_buffer[offset + index];
                file.pixel_data[(p * 4) + 1] = bmp_file_buffer[offset + index + 1];
                file.pixel_data[(p * 4)] = bmp_file_buffer[offset + index + 2];
                file.pixel_data[(p * 4) + 3] = bmp_file_buffer[offset + index + 3];
                p++;
            }
        }
    }
    else
    {
        printf("Bmp specified bits per pixel not supported\n");
        return false;
    }

    delete[] bmp_file_buffer;

    return true; 
}

void
create_image(e2_bmp_file& bmp, e2_image& image)
{
    image.width = bmp.image_header.image_width;
    image.height = bmp.image_header.image_height;
    image.pixels = bmp.pixel_data;
}
