#ifndef H_BAL_SHADERUTILITY
#define H_BAL_SHADERUTILITY

#include <stdio.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

bool 
CreateShaderProgram(GLuint* Program, char* VertexShader, char* FragmentShader);

#endif
