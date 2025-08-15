#ifndef SCENE_H
#define SCENE_H

#include <GLFW/glfw3.h>
#include <stdint.h>

typedef struct
{
    char name[128];
    struct SceneNode** children;    
    struct SceneNode* parent;
    uint64_t verticesStart, verticesLen;
    uint64_t indicesStart, indicesLen;
    GLuint shader;

}SceneNode;

typedef struct
{
    SceneNode* root;
    uint16_t numNodes;
}SceneTree;

SceneTree* createSceneTree();

void transitionScene(SceneNode* newScene);
void setTree(SceneTree* t);

#endif