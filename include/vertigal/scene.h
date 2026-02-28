#ifndef SCENE_H
#define SCENE_H

#include <GLFW/glfw3.h>
#include <stdint.h>

#include "cglm/mat4.h"
#include "vertigal/models.h"
#include "vertigal/camera.h"

union RootType
{
    VG_PLAYER_CAMERA camera;
    vertigal_handle nodeID;
};

typedef struct
{
    #ifdef DEBUG
    char name[128];
    #endif
    uint32_t children[4];    
    uint32_t parent; 
    vertigal_handle nodeID;
    GLuint program;
}SceneNode;

typedef struct
{
    SceneNode* children[4];     
    union RootType type;
    GLuint program;
}SceneRoot;

typedef struct
{
    SceneRoot root;
    uint32_t numNodes;
    uint64_t verticesStart[128];
    uint64_t verticesLen[128];
    uint64_t indicesStart[128];
    uint64_t indicesLen[128];
    mat4 transform[128];
    mat4 scale[128];
}SceneTree;

typedef struct
{
    SceneTree* tree;
    SceneNode* nodePool;
    uint32_t root;
    uint32_t arenaSize;
    uint32_t arenaUsed;
    bool initialized;
    bool slotInUse[128];
}VERTIGAL_SCENE_ARENA;

typedef struct 
{
    uint32_t nodes; //number of nodes in the stack
    uint32_t* nodeIndex; //index of our node in the memory arena

}SceneStack;


VERTIGAL_SCENE_ARENA* createScene(uint32_t numNodes, VG_PLAYER_CAMERA* cam);
uint32_t addNodeToScene(uint32_t parent, uint32_t child, VERTIGAL_SCENE_ARENA* arena);
void initSceneGraphArena(uint32_t numNodes, VERTIGAL_SCENE_ARENA* arena, VG_PLAYER_CAMERA* cam);
void transitionScene(VERTIGAL_SCENE_ARENA* newScene, VERTIGAL_MODEL_ARENA* models);
void setTree(SceneTree* t);
void setCurrentSceneToRoot();
#endif