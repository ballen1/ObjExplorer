#ifndef H_E2_RENDER
#define H_E2_RENDER

#include <vector>
#include <glad/glad.h>

#include "e2_mesh.h"

class e2_render
{
public:
    e2_render();
    ~e2_render();

    void submit_render_mesh(e2_mesh *mesh);
    void update_render_buffer();
    void render_frame();

    void set_shader_program(GLuint shader);

private:
    std::vector<e2_mesh*> render_meshes;
    
    std::vector<float> render_buffer_data;
    std::vector<unsigned int> render_element_buffer;

    GLuint shader_program;

    unsigned int vbo;
    unsigned int vao;
    unsigned int ebo;
};

#endif
