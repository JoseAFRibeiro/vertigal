#include <cglm/vec3.h>
#include <cglm/vec2.h>
#include <cglm/cam.h>
#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include  <string.h>
#include "vertigal/camera.h"

void processMovement(GLFWwindow* win, float deltaTime, VG_PLAYER_CAMERA* cam, mat4* viewMatrix)
{   
    // const float camSpeed = 0.05f;
    // vec3 tempVec3;

    // if(glfwGetKey(win, GLFW_KEY_W) == GLFW_PRESS)
    // {
    //     glm_vec3_scale(cam->__cameraFront, camSpeed, tempVec3);
    //     glm_vec3_add(tempVec3, cam->cameraPosition, cam->cameraPosition);
    //     glm_vec3_add(cam->cameraPosition, cam->__cameraFront, tempVec3);
    // }

    // if(glfwGetKey(win, GLFW_KEY_S) == GLFW_PRESS)
    // {
    //     //glm_vec3_muladd((float*) (camSpeed * -1), cam->__cameraFront, cam->cameraPosition);
    // }

}