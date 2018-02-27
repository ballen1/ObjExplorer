#include "obj_viewer.h"
#include "obj_file.h"
#include "BAL_ShaderUtility.h"
#include "obj_math.h"
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

void framebuffer_resize_callback(GLFWwindow* window, int width, int height);

int
main(int argc, char** argv)
{
    GLFWwindow* window;

    if (!glfwInit())
    {
        std::cerr << "Failed to initialize GLFW\n";
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(OBJ_VIEWER_WINDOW_WIDTH, OBJ_VIEWER_WINDOW_HEIGHT,
                                "3D Model Viewer", nullptr, nullptr);

    if (!window)
    {
        std::cerr << "Failed to create GLFW window\n";
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_resize_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cerr << "Failed to get OpenGL proc address\n";
        glfwTerminate();
        return -1;
    }

    glEnable(GL_DEPTH_TEST);
    glViewport(0, 0, OBJ_VIEWER_VIEWPORT_WIDTH, OBJ_VIEWER_VIEWPORT_HEIGHT);

    GLuint shader_program;
    if (CreateShaderProgram(&shader_program, "data\\shaders\\vertex.vert", "data\\shaders\\fragment.frag"))
    {

        obj_file capsule("donut5.obj");
        capsule.read_file();

        vec3f* verts;
        int num_verts;

        capsule.get_vertices(&verts, num_verts);

        face3f* faces;
        int num_faces;

        capsule.get_faces(&faces, num_faces);

        vec3f* normals;
        int num_normals;

        capsule.get_vertex_normals(&normals, num_normals);

        std::vector<float> vert_arr;
        std::vector<unsigned int> vert_indices;
        std::vector<float> vert_normals;

        for (int v = 0; v < num_verts; v++)
        {
            vert_arr.push_back(verts[v].x);
            vert_arr.push_back(verts[v].y);
            vert_arr.push_back(verts[v].z);
            vert_arr.push_back(normals[v].x);
            vert_arr.push_back(normals[v].y);
            vert_arr.push_back(normals[v].z);
        }

        for (int i = 0; i < num_faces; i++)
        {
            vert_indices.push_back(faces[i].v1);
            vert_indices.push_back(faces[i].v2);
            vert_indices.push_back(faces[i].v3);
        }

        glUseProgram(shader_program);

        unsigned int VBO, VAO, EBO;
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);

        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, vert_arr.size()*sizeof(float), vert_arr.data(), GL_STATIC_DRAW);

        glGenBuffers(1, &EBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, vert_indices.size()*sizeof(int), vert_indices.data(), GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);

        // Matrix stuff is gonna go here.
        mat4f model = Mat4f();
        mat4f view = translation_mat4f(0.0f, -5.0f, -200.0f);

        perspective_projection p;
        
        p.width = OBJ_VIEWER_WINDOW_WIDTH;
        p.height = OBJ_VIEWER_WINDOW_HEIGHT;
        p.vertical_fov = 45.0f;
        p.near_plane = 0.1f;
        p.far_plane = 1000.0f;
        
        mat4f projection_mat = get_perspective_projection(p);

        int uniform_loc = glGetUniformLocation(shader_program, "model");
        glUniformMatrix4fv(uniform_loc, 1, GL_FALSE, model.mat); 

        uniform_loc = glGetUniformLocation(shader_program, "view");
        glUniformMatrix4fv(uniform_loc, 1, GL_FALSE, view.mat);

        uniform_loc = glGetUniformLocation(shader_program, "projection");
        glUniformMatrix4fv(uniform_loc, 1, GL_FALSE, projection_mat.mat);
    
        while (!glfwWindowShouldClose(window))
        {
            glClearColor(0.8f, 0.2f, 0.5f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            glBindVertexArray(VAO);
            glDrawElements(GL_TRIANGLES, vert_indices.size(), GL_UNSIGNED_INT, 0);
            glBindVertexArray(0);

            glfwSwapBuffers(window);

            glfwPollEvents();
        }
    }
}

void
framebuffer_resize_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}
