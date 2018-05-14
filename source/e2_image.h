#ifndef H_E2_IMAGE
#define H_E2_IMAGE

#include <stdint.h>

struct e2_image
{
    size_t width;
    size_t height;

    uint8_t* pixels;
};


#endif
