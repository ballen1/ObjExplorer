#include "e2_gfx_primitive.h"

e2_plane
define_plane(float length)
{
    float extent = length / 2.0;

    e2_plane plane;

    plane.points[0].x = extent;
    plane.points[0].y = 0.0;
    plane.points[0].z = extent;
    plane.uvs[0].u = 1.0;
    plane.uvs[0].v = 1.0;

    plane.points[1].x = extent;
    plane.points[1].y = 0.0;
    plane.points[1].z = -extent;
    plane.uvs[1].u = 1.0;
    plane.uvs[1].v = 0.0;
    
    plane.points[2].x = -extent;
    plane.points[2].y = 0.0;
    plane.points[2].z = -extent;
    plane.uvs[2].u = 0.0;
    plane.uvs[2].v = 0.0;
    
    plane.points[3].x = -extent;
    plane.points[3].y = 0.0;
    plane.points[3].z = extent;
    plane.uvs[3].u = 0.0;
    plane.uvs[3].v = 1.0;

    plane.normal.x = 0.0;
    plane.normal.y = 1.0;
    plane.normal.z = 0.0;

    return plane;
}

e2_box
define_box(float length)
{
    float extent = length / 2.0;

    e2_box box;

    box.points[0].x = extent;
    box.points[0].y = -extent;
    box.points[0].z = extent;

    box.points[1].x = extent;
    box.points[1].y = extent;
    box.points[1].z = extent;

    box.points[2].x = extent;
    box.points[2].y = extent;
    box.points[2].z = -extent;

    box.points[3].x = extent;
    box.points[3].y = -extent;
    box.points[3].z = -extent;

    box.points[4].x = -extent;
    box.points[4].y = -extent;
    box.points[4].z = -extent;

    box.points[5].x = -extent;
    box.points[5].y = -extent;
    box.points[5].z = extent;

    box.points[6].x = -extent;
    box.points[6].y = extent;
    box.points[6].z = extent;

    box.points[7].x = -extent;
    box.points[7].y = extent;
    box.points[7].z = -extent;

    return box;
}
