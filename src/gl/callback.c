#include <stdio.h>
#include "glad/glad.h"
#include <GLFW/glfw3.h>

#define TEXT_RED "\033[1;31m"
#define TEXT_NORMAL "\033[1;0m"

void keyPressedCallback(GLFWwindow* win, GLint key, GLint scancode, GLint action, GLint mods)
{
    if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(win, GL_TRUE);
}

void DebugCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam)
{
    fprintf(stderr, "GL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s\n",
           ( type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : "" ),
            type, severity, message);
}

void errorCallback(GLint error, const char* errorString)
{
    fprintf(stderr,"%s ERROR %s %d: %s\n", TEXT_RED, TEXT_NORMAL, error, errorString);
    return;
}

void frameBufferSizeCallback(GLFWwindow *win, int width, int height)
{
    glViewport(0, 0, width, height);
    return;
}
