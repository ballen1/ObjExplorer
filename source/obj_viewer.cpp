#include "obj_viewer.h"
#include "obj_file.h"
#include "BAL_ShaderUtility.h"
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

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

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cerr << "Failed to get OpenGL proc address\n";
        glfwTerminate();
        return -1;
    }

    glViewport(0, 0, OBJ_VIEWER_VIEWPORT_WIDTH, OBJ_VIEWER_VIEWPORT_HEIGHT);

    GLuint ShaderProgram;
    if (CreateShaderProgram(&ShaderProgram, "data\\shaders\\vertex.vert", "data\\shaders\\fragment.frag"))
    {
        while (!glfwWindowShouldClose(window))
        {
            glClearColor(0.8f, 0.2f, 0.5f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            glfwSwapBuffers(window);

            glfwPollEvents();
        }
    }
}
