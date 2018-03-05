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

typedef struct
{
    vec3f position;
    float yaw;
    float pitch;
} first_person_camera;

inline
vec3f
Vec3f(float x, float y, float z)
{
    vec3f v;
    v.x = x;
    v.y = y;
    v.z = z;

    return v;
}

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
vec3f
s_multiply(vec3f& v, float s)
{
    vec3f new_v;
    new_v.x = v.x * s;
    new_v.y = v.y * s;
    new_v.z = v.z * s;

    return new_v;
}

inline
vec3f
add(vec3f v1, vec3f v2)
{
    vec3f v3;
    v3.x = v1.x + v2.x;
    v3.y = v1.y + v2.y;
    v3.z = v1.z + v2.z;

    return v3;
}    

inline
vec3f
subtract(vec3f v1, vec3f v2)
{
    vec3f v3;
    v3.x = v2.x - v1.x;
    v3.y = v2.y - v1.y;
    v3.z = v2.z - v1.z;

    return v3;
}

inline
float
dot_product(vec3f& v1, vec3f v2)
{
    return ((v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z));
}

inline
vec3f
cross_product(vec3f v1, vec3f v2)
{
    vec3f v3;

    v3.x = (v1.y * v2.z) - (v1.z * v2.y);
    v3.y = (v1.z * v2.x) - (v1.x * v2.z);
    v3.z = (v1.x * v2.y) - (v1.y * v2.x);

    return v3;
}

inline
float
magnitude(vec3f& v)
{
    return sqrt((v.x*v.x) + (v.y*v.y) + (v.z*v.z));
}

inline
vec3f
normalize(vec3f v)
{
    float mag = magnitude(v);
    
    vec3f norm;
    norm.x = v.x / mag;
    norm.y = v.y / mag;
    norm.z = v.z / mag;

    return norm;
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

inline
mat4f
get_view_matrix(first_person_camera& camera)
{
    mat4f view_mat;
    float pitch_cos, pitch_sin, yaw_cos, yaw_sin;
    vec3f u, v, w;

    pitch_cos = cos(DEG2RAD * camera.pitch);
    pitch_sin = sin(DEG2RAD * camera.pitch);
    yaw_cos = cos(DEG2RAD * camera.yaw);
    yaw_sin = sin(DEG2RAD * camera.yaw);

    u = Vec3f(yaw_cos, 0.0f, yaw_sin);
    v = Vec3f((pitch_sin * yaw_sin), pitch_cos, -(pitch_sin * yaw_cos));
    w = Vec3f(-(pitch_cos * yaw_sin), pitch_sin, (pitch_cos * yaw_cos));

    view_mat.mat[0] = u.x;
    view_mat.mat[1] = v.x;
    view_mat.mat[2] = w.x;
    view_mat.mat[3] = 0.0f;

    view_mat.mat[4] = u.y;
    view_mat.mat[5] = v.y;
    view_mat.mat[6] = w.y;
    view_mat.mat[7] = 0.0f;

    view_mat.mat[8] = u.z;
    view_mat.mat[9] = v.z;
    view_mat.mat[10] = w.z;
    view_mat.mat[11] = 0.0f;

    view_mat.mat[12] = -dot_product(u, camera.position);
    view_mat.mat[13] = -dot_product(v, camera.position);
    view_mat.mat[14] = -dot_product(w, camera.position);
    view_mat.mat[15] = 1.0f;

    return view_mat;
}

inline
vec3f
get_first_person_camera_front(first_person_camera& camera)
{
    vec3f front;

    front.x = (cos(DEG2RAD * camera.pitch) * sin(DEG2RAD * camera.yaw));
    front.y = -sin(DEG2RAD * camera.pitch);
    front.z = -(cos(DEG2RAD * camera.pitch) * cos(DEG2RAD * camera.yaw));

    return normalize(front);
}

inline
vec3f
get_first_person_camera_right(first_person_camera& camera)
{
    vec3f up = Vec3f(0.0f, 1.0f, 0.0f);
    vec3f front = get_first_person_camera_front(camera);

    return cross_product(normalize(front), up);
}

#endif
