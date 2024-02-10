#include "vertigal/camera.h" 
#include <string.h>

VG_PLAYER_CAMERA cameraSetup()
{   
    vec3 tempVec3;
    vec3 center = {0.0f, 0.0f, 0.0f};
    
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
    glm_cross(camera.__cameraUp, camera.cameraDirection, camera.__cameraRight);
    glm_normalize_to(camera.__cameraRight, camera.__cameraRight);
    glm_cross(camera.cameraDirection, camera.__cameraRight, camera.__cameraUp);
    glm_lookat(camera.cameraPosition, center, camera.__cameraUp, camera.lookat);

    return camera;
}

