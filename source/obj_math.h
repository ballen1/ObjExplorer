#ifndef H_OBJ_MATH
#define H_OBJ_MATH

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

#endif
