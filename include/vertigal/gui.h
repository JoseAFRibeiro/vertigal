#ifndef E__PROGRAMAS_C_VERTIGAL_INCLUDE_VERTIGAL_GUI_H_
#define E__PROGRAMAS_C_VERTIGAL_INCLUDE_VERTIGAL_GUI_H_
#include <GLFW/glfw3.h>
#include "cglm/vec3.h"
uint8_t guiInit(GLFWwindow *win);
void guiRender(GLFWwindow *win);
void setPosition(vec3 vec);
#endif