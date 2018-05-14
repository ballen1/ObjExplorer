#ifndef H_E2_GFX_PRIMITIVE
#define H_E2_GFX_PRIMITIVE

#include "e2_math.h"

#define GFX_PRIM_PLANE_POINT_COUNT 4

struct e2_plane
{
    vec3f points[4];
    tex2f uvs[4];
    vec3f normal;
};

struct e2_box
{
    vec3f points[8];
};

e2_plane
define_plane(float length);

e2_box
define_box(float length);

#endif
