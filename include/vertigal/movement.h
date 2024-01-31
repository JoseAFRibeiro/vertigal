#ifndef MOVEMENT_H_
#define MOVEMENT_H_

#include "cglm/mat4.h"
#include "vertigal/camera.h"
#include "glad/glad.h"
#include <GLFW/glfw3.h>

void processMovement(GLFWwindow* win, float deltaTime, VG_PLAYER_CAMERA* cam,  mat4* viewMatrix);

#endif