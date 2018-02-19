#include "obj_file.h"

#include <iostream>
#include <fstream>
#include <cstring>
#include <sstream>

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
    std::ifstream in_file(file_path);

    if (in_file.is_open())
    {
        std::string file_line;
        while(std::getline(in_file, file_line))
        {
            std::istringstream data(file_line); 
            std::string word;

            if (data >> word)
            {
                if (word == "v")
                {
                    vec3f vertex;
                    
                    if (!(data >> vertex.x >> vertex.y >> vertex.z))
                    {
                        std::cerr << "Error: unsupported vertex found in .obj file <" + file_path + ">\n";
                        return false;
                    }

                    vertices.push_back(vertex);
                }
                else if (word == "vt")
                {
                    tex2f tex_vert;
                    if (!(data >> tex_vert.u >> tex_vert.v))
                    {
                        std::cerr << "Error: unsupported texture vertex found in .obj file <" + file_path + ">\n";
                        return false;
                    }
                    uvs.push_back(tex_vert);
                }
                else if (word == "vn")
                {
                    vec3f vert_norm;
                    if (!(data >> vert_norm.x >> vert_norm.y >> vert_norm.z))
                    {
                        std::cerr << "Error: unsupported vertex normal found in .obj file <" + file_path + ">\n";
                        return false;
                    }
                    vertex_normals.push_back(vert_norm);
                }
                else if (word == "f")
                {
                }
            }
        }
    }
    else
    {
        std::cerr << "Error: could not open .obj file <" + file_path + ">\n";
        std::cerr << "strerror: " << std::strerror(errno) << "\n";
        return false;
    }

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
obj_file::get_vertex_normals(vec3f* normal_arr, int &size)
{
    if (size > 0)
    {
        normal_arr = &vertex_normals.front();
        size = vertex_normals.size();
    }
    else
    {
        normal_arr = nullptr;
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
