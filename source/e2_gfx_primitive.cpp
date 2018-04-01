#include "e2_gfx_primitive.h"

bool
define_plane(float length, vec3f* points_arr, int points_arr_size)
{
    if (points_arr_size < GFX_PRIM_PLANE_POINT_COUNT)
    {
        return false;
    }

    float extent = length / 2.0;

    points_arr[0].x = extent;
    points_arr[0].y = 0.0;
    points_arr[0].z = extent;

    points_arr[1].x = extent;
    points_arr[1].y = 0.0;
    points_arr[1].z = -extent;
    
    points_arr[2].x = -extent;
    points_arr[2].y = 0.0;
    points_arr[2].z = -extent;
    
    points_arr[3].x = -extent;
    points_arr[3].y = 0.0;
    points_arr[3].z = extent;

    return true;
}
