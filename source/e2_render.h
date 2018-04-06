#ifndef H_E2_RENDER
#define H_E2_RENDER

#include <vector>
#include <glad/glad.h>

#include "e2_mesh.h"
#include "e2_render_object.h"
#include "e2_math.h"

class e2_render
{
public:
    e2_render();
    ~e2_render();

    void submit_render_object(e2_render_object* object);
    void update_render_buffer();
    void render_frame();

    void set_shader_program(GLuint shader);
    void set_active_camera(first_person_camera* cam);
    void set_active_projection(perspective_projection* proj);

private:
    std::vector<e2_render_object*> render_objects;
    
    std::vector<float> render_buffer_data;
    std::vector<unsigned int> render_element_buffer;

    GLuint shader_program;

    first_person_camera* camera;
    perspective_projection* projection;

    unsigned int vbo;
    unsigned int vao;
    unsigned int ebo;
};

#endif
