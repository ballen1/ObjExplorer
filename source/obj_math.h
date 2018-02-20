#ifndef H_OBJ_MATH
#define H_OBJ_MATH

#include <math.h>

#define DEG2RAD 0.0174533

typedef struct
{
    float u;
    float v;
} tex2f;

typedef struct
{
    float x;
    float y;
    float z;
} vec3f;

typedef struct
{
    int v1;
    int v2;
    int v3;

    int vn1;
    int vn2;
    int vn3;

    int vt1;
    int vt2;
    int vt3;
} face3f;

typedef struct
{
    float mat[16];
} mat4f;

typedef struct
{
    float width;
    float height;

    float vertical_fov;

    float near;
    float far;
} perspective_projection;

inline
mat4f
get_perspective_projection(perspective_projection& perspective)
{
    mat4f proj;

    float aspect_ratio = perspective.width / perspective.height;
    float tan_factor = tanf((DEG2RAD * perspective.vertical_fov) / 2.0);

    proj.mat[0] = 1.0 / (aspect_ratio * tan_factor);
    proj.mat[1] = 0.0f;
    proj.mat[2] = 0.0f;
    proj.mat[3] = 0.0f;

    proj.mat[4] = 0.0f;
    proj.mat[5] = (1.0 / tan_factor);
    proj.mat[6] = 0.0f;
    proj.mat[7] = 0.0f;

    proj.mat[8] = 0.0f;
    proj.mat[9] = 0.0f;
    proj.mat[10] = (perspective.near + perspective.far) / (perspective.near - perspective.far);
    proj.mat[11] = -1.0f;

    proj.mat[12] = 0.0f;
    proj.mat[13] = 0.0f;
    proj.mat[14] = (2 * perspective.far * perspective.near ) / (perspective.near - perspective.far);
    proj.mat[15] = 0.0f;

    return proj;
}

#endif
