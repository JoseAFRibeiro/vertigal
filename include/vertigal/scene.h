#ifndef SCENE_H
#define SCENE_H

#include <GLFW/glfw3.h>
#include <stdint.h>

typedef struct
{
    char name[128];
    struct SceneNode** children;    
    struct SceneNode* parent;
    float *vertices;
    uint32_t *indices;

}SceneNode;

typedef struct
{
    SceneNode* root;
    uint16_t numNodes;
}SceneTree;


#endif