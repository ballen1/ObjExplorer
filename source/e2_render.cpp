#include "e2_render.h"

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
e2_render::submit_render_mesh(e2_mesh *mesh)
{
    render_meshes.push_back(mesh);
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

/*
void
e2_render::update_render_buffer()
{
    for (int m = 0; m < render_meshes.size(); m++)
    {
        size_t v_count = render_meshes[m]->get_vertex_count();
        size_t n_count = render_meshes[m]->get_normal_count();

        float* v_data = render_meshes[m]->get_raw_vertex_data();
        float* n_data = render_meshes[m]->get_raw_normal_data();

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

        for (int e = 0; e < render_meshes[m]->get_face_data_size(); e++)
        {
            render_element_buffer.push_back(render_meshes[m]->get_raw_face_data()[e]);
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
*/

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
