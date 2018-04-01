#include "e2_render.h"

e2_renderer::e2_renderer()
{
}

e2_renderer::~e2_renderer()
{
}

void
e2_renderer::submit_render_mesh(e2_mesh *mesh)
{
    render_meshes.push_back(mesh);
}
