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
    unsigned char header_size[4];
    unsigned char image_width[4];
    unsigned char image_height[4];
    unsigned char planes[2];
    unsigned char bit_count[2];
};

struct e2_bmp_file
{
    e2_bmp_file_header file_header;
    e2_bmp_file_image_header image_header;

    unsigned char* pixel_data;
};

bool
load_bmp_file(const char* file_path, e2_bmp_file& file);

#endif
