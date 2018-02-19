#include "obj_file.h"

#include <iostream>

obj_file::obj_file()
    : file_path("")
{

}

obj_file::obj_file(std::string file_path)
    : file_path(file_path)
{

}

obj_file::~obj_file()
{

}

bool
obj_file::read_file()
{
    return true;
}

void
obj_file::get_vertices(vec3f* vert_arr, int& size)
{
    if (size > 0)
    {
        vert_arr = &vertices.front();
        size = vertices.size();
    }
    else
    {
        vert_arr = nullptr;
        size = 0;
    }
}

void
obj_file::get_uvs(tex2f* uv_arr, int& size)
{
    if (size > 0)
    {
        uv_arr = &uvs.front();
        size = uvs.size();
    }
    else
    {
        uv_arr = nullptr;
        size = 0;
    }
}

void
obj_file::get_faces(face3f* face_arr, int& size)
{
    if (size > 0)
    {
        face_arr = &faces.front();
        size = faces.size();
    }
    else
    {
        face_arr = nullptr;
        size = 0;
    }
}
