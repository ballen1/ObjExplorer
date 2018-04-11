#ifndef H_E2_RENDER_OBJECT
#define H_E2_RENDER_OBJECT

#include "e2_math.h"
#include "e2_mesh.h"
#include "e2_material.h"

class e2_render_object
{
public:
    e2_render_object(e2_mesh* render_mesh, mat4f model_mat);
    ~e2_render_object();

    e2_mesh* get_mesh();
    e2_material* get_material();
    mat4f get_mesh_model_transformation();

    void assign_material(e2_material* mat);

private:
    e2_mesh* mesh;
    e2_material* material;
    mat4f model_matrix; 
};

#endif
