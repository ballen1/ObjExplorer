#include "obj_viewer.h"
#include "obj_file.h"
#include "BAL_ShaderUtility.h"
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

    glViewport(0, 0, OBJ_VIEWER_VIEWPORT_WIDTH, OBJ_VIEWER_VIEWPORT_HEIGHT);

    GLuint shader_program;
    if (CreateShaderProgram(&shader_program, "data\\shaders\\vertex.vert", "data\\shaders\\fragment.frag"))
    {
        glUseProgram(shader_program);

        unsigned int VBO, VAO, EBO;
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);

        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(test_vertices), test_vertices, GL_STATIC_DRAW);

        glGenBuffers(1, &EBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(test_indices), test_indices, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        while (!glfwWindowShouldClose(window))
        {
            glClearColor(0.8f, 0.2f, 0.5f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            glBindVertexArray(VAO);
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
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
