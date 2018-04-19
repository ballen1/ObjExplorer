#include "e2_render.h"

#include "e2_material.h"
#include "e2_types.h"
#include <string>

e2_render::e2_render()
{
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ebo);
}

e2_render::~e2_render()
{
}

void
e2_render::submit_render_object(e2_render_object* object)
{
    render_objects.push_back(object);
}

void
e2_render::update_render_buffer()
{
    for (int m = 0; m < render_objects.size(); m++)
    {
        e2_mesh* render_mesh = render_objects[m]->get_mesh();

        if (render_mesh)
        {
            size_t v_count = render_mesh->get_vertex_count();
            size_t n_count = render_mesh->get_normal_count();

            float* v_data = render_mesh->get_raw_vertex_data();
            float* n_data = render_mesh->get_raw_normal_data();

            if (v_count == n_count)
            {
                for (int i = 0; i < v_count; i++)
                {
                    render_buffer_data.push_back(v_data[(i * 3)]);
                    render_buffer_data.push_back(v_data[(i * 3) + 1]);
                    render_buffer_data.push_back(v_data[(i * 3) + 2]);
                    render_buffer_data.push_back(n_data[(i * 3)]);
                    render_buffer_data.push_back(n_data[(i * 3) + 1]);
                    render_buffer_data.push_back(n_data[(i * 3) + 2]);
                }
            }

            for (int e = 0; e < render_mesh->get_face_data_size(); e++)
            {
                render_element_buffer.push_back(render_mesh->get_raw_face_data()[e]);
            }
        }
    }

    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, render_buffer_data.size() * sizeof(float), render_buffer_data.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, render_element_buffer.size()*sizeof(unsigned int), render_element_buffer.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
}

void
e2_render::render_frame()
{
    glClearColor(0.8f, 0.2f, 0.5f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glBindVertexArray(vao);

    unsigned int element_offset = 0;
    unsigned int vertex_offset = 0;
    for (int m = 0; m < render_objects.size(); m++)
    {
        e2_mesh* render_mesh = render_objects[m]->get_mesh();

        int uniform_loc = glGetUniformLocation(shader_program, "model");
        glUniformMatrix4fv(uniform_loc, 1, GL_FALSE, render_objects[m]->get_mesh_model_transformation().mat);

        uniform_loc = glGetUniformLocation(shader_program, "colour");
        e2_material* mat = render_objects[m]->get_material();
        glUniform3f(uniform_loc, mat->colour.r, mat->colour.g, mat->colour.b);

        glDrawElementsBaseVertex(GL_TRIANGLES, render_mesh->get_face_data_size(), GL_UNSIGNED_INT, (GLvoid*)(element_offset * sizeof(unsigned int)), vertex_offset);
        element_offset += render_mesh->get_face_data_size();
        vertex_offset += render_mesh->get_vertex_count();
    }

    glBindVertexArray(0);
}

void
e2_render::set_shader_program(GLuint shader)
{
    shader_program = shader;
    glUseProgram(shader_program);
}

void
e2_render::set_active_camera(first_person_camera* cam)
{
    camera = cam;
}

void
e2_render::set_active_projection(perspective_projection* proj)
{
    projection = proj;
}

void
e2_render::add_pointlight(e2_pointlight* light)
{
    point_lights.push_back(light);

    int uniform_loc = glGetUniformLocation(shader_program, "active_point_lights");
    glUniform1i(uniform_loc, point_lights.size());

    int index = point_lights.size() - 1;

    std::string position_str("point_lights[" + std::to_string(index) + "].position");
    std::string ambient_colour_str("point_lights[" + std::to_string(index) + "].ambient_colour");
    std::string diffuse_colour_str("point_lights[" + std::to_string(index) + "].diffuse_colour");
    std::string atten_const_str("point_lights[" + std::to_string(index) + "].constant");
    std::string atten_linear_str("point_lights[" + std::to_string(index) + "].linear");
    std::string atten_quadratic_str("point_lights[" + std::to_string(index) + "].quadratic");

    uniform_loc = glGetUniformLocation(shader_program, position_str.c_str()); 
    glUniform3f(uniform_loc, light->position.x, light->position.y, light->position.z);

    uniform_loc = glGetUniformLocation(shader_program, ambient_colour_str.c_str());
    glUniform3f(uniform_loc, light->ambient_colour.r, light->ambient_colour.g, light->ambient_colour.b);

    uniform_loc = glGetUniformLocation(shader_program, diffuse_colour_str.c_str());
    glUniform3f(uniform_loc, light->diffuse_colour.r, light->diffuse_colour.g, light->diffuse_colour.b);

    uniform_loc = glGetUniformLocation(shader_program, atten_const_str.c_str());
    glUniform1f(uniform_loc, light->atten_constant);

    uniform_loc = glGetUniformLocation(shader_program, atten_linear_str.c_str());
    glUniform1f(uniform_loc, light->atten_linear);

    uniform_loc = glGetUniformLocation(shader_program, atten_quadratic_str.c_str());
    glUniform1f(uniform_loc, light->atten_quadratic);
}
