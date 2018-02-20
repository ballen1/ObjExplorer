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
    unsigned int v1;
    unsigned int v2;
    unsigned int v3;

    unsigned int vn1;
    unsigned int vn2;
    unsigned int vn3;

    unsigned int vt1;
    unsigned int vt2;
    unsigned int vt3;
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

    float near_plane;
    float far_plane;
} perspective_projection;

inline
mat4f
Mat4f()
{
    mat4f mat;

    mat.mat[0] = 1.0f;
    mat.mat[1] = 0.0f;
    mat.mat[2] = 0.0f;
    mat.mat[3] = 0.0f;

    mat.mat[4] = 0.0f;
    mat.mat[5] = 1.0f;
    mat.mat[6] = 0.0f;
    mat.mat[7] = 0.0f;

    mat.mat[8] = 0.0f;
    mat.mat[9] = 0.0f;
    mat.mat[10] = 1.0f;
    mat.mat[11] = 0.0f;

    mat.mat[12] = 0.0f;
    mat.mat[13] = 0.0f;
    mat.mat[14] = 0.0f;
    mat.mat[15] = 1.0f;

    return mat;
}

inline
mat4f
translation_mat4f(float x, float y, float z)
{
    mat4f mat = Mat4f();

    mat.mat[12] = x;
    mat.mat[13] = y;
    mat.mat[14] = z;

    return mat;
}

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
    proj.mat[10] = (perspective.near_plane + perspective.far_plane) / (perspective.near_plane - perspective.far_plane);
    proj.mat[11] = -1.0f;

    proj.mat[12] = 0.0f;
    proj.mat[13] = 0.0f;
    proj.mat[14] = (2 * perspective.far_plane * perspective.near_plane ) / (perspective.near_plane - perspective.far_plane);
    proj.mat[15] = 0.0f;

    return proj;
}

#endif
