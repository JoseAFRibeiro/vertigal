#ifndef GLFUNCS_H_
#define GLFUNCS_H_

#include <stdint.h>
#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include "vertigal/glstrcuts.h"

GLFWwindow* glInit(void);
GLuint compileShader(const char* path, GLenum shaderType);
GLuint compileShaderProgram(VG_shader_packet p);
uint8_t rendererSetup(void);
void renderLoop(GLFWwindow* win);

#endif 