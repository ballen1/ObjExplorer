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

    box.normals[0].x = 1.0;
    box.normals[0].y = 0.0;
    box.normals[0].z = 0.0;
    
    box.normals[1].x = 0.0;
    box.normals[1].y = 1.0;
    box.normals[1].z = 0.0;

    box.normals[2].x = 0.0;
    box.normals[2].y = 0.0;
    box.normals[2].z = 1.0;

    box.normals[3].x = -1.0;
    box.normals[3].y = 0.0;
    box.normals[3].z = 0.0;

    box.normals[4].x = 0.0;
    box.normals[4].y = -1.0;
    box.normals[4].z = 0.0;
    
    box.normals[5].x = 0.0;
    box.normals[5].y = 0.0;
    box.normals[5].z = -1.0;

    box.faces[0] = 1;
    box.faces[1] = 0;
    box.faces[2] = 3;

    box.faces[3] = 3;
    box.faces[4] = 2;
    box.faces[5] = 1;

    box.faces[6] = 1;
    box.faces[7] = 2;
    box.faces[8] = 7;

    box.faces[9] = 7;
    box.faces[10] = 6;
    box.faces[11] = 1;

    box.faces[12] = 1;
    box.faces[13] = 6;
    box.faces[14] = 5;

    box.faces[15] = 5;
    box.faces[16] = 0;
    box.faces[17] = 1;

    box.faces[18] = 6;
    box.faces[19] = 5;
    box.faces[20] = 4;

    box.faces[21] = 4;
    box.faces[22] = 7;
    box.faces[23] = 6;

    box.faces[24] = 4;
    box.faces[25] = 5;
    box.faces[26] = 0;

    box.faces[27] = 0;
    box.faces[28] = 3;
    box.faces[29] = 4;

    box.faces[30] = 4;
    box.faces[31] = 3;
    box.faces[32] = 7;

    box.faces[33] = 7;
    box.faces[34] = 3;
    box.faces[35] = 2;
    
    return box;
}
