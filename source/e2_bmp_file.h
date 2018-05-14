#ifndef H_E2_BMP_FILE
#define H_E2_BMP_FILE

#include <stdint.h>

#define E2_BMP_FILE_HEADER_LEN 14
#define E2_BMP_FILE_IMAGE_HEADER_LEN 16

struct e2_bmp_file_header
{
    uint8_t type[2];
    uint32_t file_size;
    uint16_t reserved1;
    uint16_t reserved2;
    uint32_t offset_bits;
};

struct e2_bmp_file_image_header
{
    uint32_t header_size;
    uint32_t image_width;
    uint32_t image_height;
    uint16_t planes;
    uint16_t bit_count;
};

struct e2_bmp_file
{
    e2_bmp_file_header file_header;
    e2_bmp_file_image_header image_header;

    uint8_t* pixel_data;
};

bool
load_bmp_file(const char* file_path, e2_bmp_file& file);

#endif
