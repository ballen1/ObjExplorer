#include "e2_render_object.h"

e2_render_object::e2_render_object(e2_mesh* render_mesh, mat4f model_mat)
    : mesh(render_mesh), model_matrix(model_mat)
{

}

e2_render_object::~e2_render_object()
{

}

e2_mesh*
e2_render_object::get_mesh()
{
    return mesh;
}

mat4f
e2_render_object::get_mesh_model_transformation()
{
    return model_matrix;
}
