#ifndef CAMERA_H_
#define CAMERA_H_

#include "cglm/vec3.h"
#include "cglm/vec2.h"
#include "cglm/mat4.h"
#include "cglm/cam.h"

typedef struct{
    vec3 cameraPosition;
    vec3 cameraTarget;
    vec3 cameraDirection;
    vec3 __cameraUp;
    vec3 __cameraRight;
    vec3 __cameraFront;
    mat4 lookat;
}VG_PLAYER_CAMERA;

VG_PLAYER_CAMERA cameraSetup();

#endif