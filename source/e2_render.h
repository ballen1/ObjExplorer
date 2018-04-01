#ifndef H_E2_RENDER
#define H_E2_RENDER

#include <vector>

#include "e2_mesh.h"

class e2_renderer
{
public:
    e2_renderer();
    ~e2_renderer();

    void submit_render_mesh(e2_mesh *mesh);

private:
    std::vector<e2_mesh*> render_meshes;
};

#endif
