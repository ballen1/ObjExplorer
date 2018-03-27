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
                    std::string v1, v2, v3;
                    if (!(data >> v1 >> v2 >> v3))
                    {
                        std::cerr << "Error: found a face with less than 3 vertices. Only triangle meshes are supported right now. .obj file <" + file_path + ">\n";
                        return false;
                    }
                    
                    face3f face;

                    char delimiter = '/';
                    
                    std::istringstream stream_v1(v1);
                    std::string token;

                    int token_idx = 0;

                    while (std::getline(stream_v1, token, delimiter))
                    {
                        if (token_idx == 0)
                        {
                            face.v1 = std::stof(token) - 1;
                        }
                        else if (token_idx == 1 && !token.empty())
                        {
                            face.vt1 = std::stof(token) - 1;
                        }
                        else if (token_idx == 2 && !token.empty())
                        {
                            face.vn1 = std::stof(token) - 1;
                        }
                        ++token_idx;
                    }

                    std::istringstream stream_v2(v2);
                    token_idx = 0;

                    while (std::getline(stream_v2, token, delimiter))
                    {
                        if (token_idx == 0)
                        {
                            face.v2 = std::stof(token) - 1;
                        }
                        else if (token_idx == 1 && !token.empty())
                        {
                            face.vt2 = std::stof(token) - 1;
                        }
                        else if (token_idx == 2 && !token.empty())
                        {
                            face.vn2 = std::stof(token) - 1;
                        }
                        ++token_idx;
                    }

                    std::istringstream stream_v3(v3);
                    token_idx = 0;

                    while (std::getline(stream_v3, token, delimiter))
                    {
                        if (token_idx == 0)
                        {
                            face.v3 = std::stof(token) - 1;
                        }
                        else if (token_idx == 1 && !token.empty())
                        {
                            face.vt3 = std::stof(token) - 1;
                        }
                        else if (token_idx == 2 && !token.empty())
                        {
                            face.vn3 = std::stof(token) - 1;
                        }
                        ++token_idx;
                    }

                    faces.push_back(face);
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

    in_file.close();

    return true;
}

void
obj_file::get_vertices(vec3f** vert_arr, int& size)
{
    if (vertices.size() > 0)
    {
        *vert_arr = vertices.data();
        size = vertices.size();
    }
    else
    {
        *vert_arr = nullptr;
        size = 0;
    }
}

void
obj_file::get_vertex_normals(vec3f** normal_arr, int &size)
{
    if (vertex_normals.size() > 0)
    {
        *normal_arr = vertex_normals.data();
        size = vertex_normals.size();
    }
    else
    {
        *normal_arr = nullptr;
        size = 0;
    }
}

void
obj_file::get_uvs(tex2f** uv_arr, int& size)
{
    if (uvs.size() > 0)
    {
        *uv_arr = uvs.data();
        size = uvs.size();
    }
    else
    {
        *uv_arr = nullptr;
        size = 0;
    }
}

void
obj_file::get_faces(face3f** face_arr, int& size)
{
    if (faces.size() > 0)
    {
        *face_arr = faces.data();
        size = faces.size();
    }
    else
    {
        *face_arr = nullptr;
        size = 0;
    }
}

bool
obj_file::has_vertex_normals()
{
    return (vertex_normals.size() > 0);
}

bool
obj_file::has_uvs()
{
    return (uvs.size() > 0);
}
