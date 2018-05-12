#ifndef H_E2_MESH
#define H_E2_MESH

#include "e2_math.h"
#include "e2_vertex.h"
#include "e2_gfx_primitive.h"
#include <string>
#include <vector>

#define E2_MESH_VERTEX_TUPLE_SIZE 3

class e2_mesh
{
public:
    e2_mesh(std::string file);
    e2_mesh(e2_plane plane);
    e2_mesh(e2_box box);
    ~e2_mesh();

    e2_vertex get_vertex(int v_idx);

    size_t get_vertex_count();
    size_t get_face_count();

    size_t get_vertex_data_size();
    size_t get_face_data_size();

    e2_vertex* get_raw_vertex_data();
    unsigned int* get_raw_face_data();

private:
    bool load_mesh_from_file(std::string file);

    std::vector<e2_vertex> vertices;
    std::vector<unsigned int> faces;
};

#endif
