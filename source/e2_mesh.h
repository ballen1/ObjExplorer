#ifndef H_E2_MESH
#define H_E2_MESH

#include "obj_math.h"
#include <string>
#include <vector>

#define E2_MESH_VERTEX_TUPLE_SIZE 3

class e2_mesh
{
public:
    e2_mesh(std::string file);
    ~e2_mesh();

    vec3f get_vertex(int v_idx);

    size_t get_vertex_count();
    size_t get_normal_count();
    size_t get_face_count();

    size_t get_vertex_data_size();
    size_t get_normal_data_size();
    size_t get_face_data_size();

    float* get_raw_vertex_data();
    float* get_raw_normal_data();
    unsigned int* get_raw_face_data();

    void set_vertex_normal(int v_idx, vec3f norm);


private:
    bool load_mesh_from_file(std::string file);

    std::vector<float> vertices;
    std::vector<unsigned int> faces;
    std::vector<float> vertex_normals;
};

#endif
