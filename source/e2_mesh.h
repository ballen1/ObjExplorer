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

private:
    bool load_mesh_from_file(std::string file);

    std::vector<float> vertices;
    std::vector<unsigned int> faces;
    std::vector<float> vertex_normals;
};

#endif
