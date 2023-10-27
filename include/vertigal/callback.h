#ifndef VERTIGAL_CALLBACK_H_
#define VERTIGAL_CALLBACK_H_

#include <GLFW/glfw3.h>


void errorCallback(GLint error, const char* errorString);
void frameBufferSizeCallback(GLFWwindow *win, int width, int height);
void DebugCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam);
void keyPressedCallback(GLFWwindow* win, GLint key, GLint scancode, GLint action, GLint mods);

#endif 