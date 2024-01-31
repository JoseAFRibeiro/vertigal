#include "vertigal/camera.h" 
#include <string.h>

VG_PLAYER_CAMERA cameraSetup()
{   
    vec3 tempVec3;

    VG_PLAYER_CAMERA camera = {
        .cameraPosition = {0.0f, 0.0f, 3.0f},
        .cameraTarget = {0.0f, 0.0f, 0.0f},
        .cameraDirection = {0.0f},
        .__cameraFront = {0.0f, 0.0f, -1.0f},
        .__cameraUp = {0.0f, 1.0f, 0.0f},
        .lookat = {0.0f}        
    };

    glm_vec3_sub(camera.cameraPosition, camera.cameraTarget, tempVec3);
    glm_normalize_to(tempVec3, camera.cameraDirection);
    glm_vec3_cross(camera.__cameraUp, camera.cameraDirection, tempVec3);
    glm_normalize_to(tempVec3, camera.__cameraRight);
    glm_vec3_cross(camera.cameraDirection, camera.__cameraRight, camera.__cameraUp);

    memset(tempVec3, 0.0f, sizeof(vec3));
    glm_lookat(camera.cameraPosition, tempVec3, camera.__cameraUp, camera.lookat);

    return camera;
}

