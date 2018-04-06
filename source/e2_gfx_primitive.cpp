#include "e2_gfx_primitive.h"

e2_plane
define_plane(float length)
{
    float extent = length / 2.0;

    e2_plane plane;

    plane.points[0].x = extent;
    plane.points[0].y = 0.0;
    plane.points[0].z = extent;

    plane.points[1].x = extent;
    plane.points[1].y = 0.0;
    plane.points[1].z = -extent;
    
    plane.points[2].x = -extent;
    plane.points[2].y = 0.0;
    plane.points[2].z = -extent;
    
    plane.points[3].x = -extent;
    plane.points[3].y = 0.0;
    plane.points[3].z = extent;

    plane.normals[0].x = 0.0;
    plane.normals[0].y = 1.0;
    plane.normals[0].z = 0.0;

    plane.normals[1].x = 0.0;
    plane.normals[1].y = 1.0;
    plane.normals[1].z = 0.0;

    plane.normals[2].x = 0.0;
    plane.normals[2].y = 1.0;
    plane.normals[2].z = 0.0;
    
    plane.normals[3].x = 0.0;
    plane.normals[3].y = 1.0;
    plane.normals[3].z = 0.0;

    plane.faces[0] = 0;
    plane.faces[1] = 3;
    plane.faces[2] = 2;
    plane.faces[3] = 2;
    plane.faces[4] = 1;
    plane.faces[5] = 0;

    return plane;
}
