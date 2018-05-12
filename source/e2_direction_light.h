#ifndef H_E2_DIRECTION_LIGHT
#define H_E2_DIRECTION_LIGHT

#include "e2_math.h"
#include "e2_colour.h"

class e2_direction_light
{
public:
    e2_direction_light();
    ~e2_direction_light();

    vec3f direction;
    e2_colour ambient;
    e2_colour diffuse;
    e2_colour specular;
};

#endif
