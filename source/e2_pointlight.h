#ifndef H_E2_POINTLIGHT
#define H_E2_POINTLIGHT

#include "e2_math.h"
#include "e2_types.h"

class e2_pointlight
{
public:
    e2_pointlight(vec3f pos, e2_colour a_col, e2_colour d_col);
    ~e2_pointlight();

    vec3f position;
    e2_colour ambient_colour;
    e2_colour diffuse_colour;
};

#endif
