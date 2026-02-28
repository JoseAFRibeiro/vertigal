#include <malloc.h>
#include <string.h>
#include "vertigal/scene.h"
#include "vertigal/models.h"
#include "vertigal/camera.h"


static SceneTree* tree;

static inline uint32_t getArenaSlot(VERTIGAL_SCENE_ARENA* arena);
static inline SceneNode* getNodeByHandle(uint32_t handle, VERTIGAL_SCENE_ARENA* arena);


VERTIGAL_SCENE_ARENA* createScene(uint32_t numNodes, VG_PLAYER_CAMERA *cam)
{   
    VERTIGAL_SCENE_ARENA* arena;
    arena = malloc(sizeof(VERTIGAL_SCENE_ARENA));
    memset(arena, 0, sizeof(VERTIGAL_SCENE_ARENA));
    initSceneGraphArena(numNodes, arena, cam);

    return arena;
}

uint32_t addNodeToScene(uint32_t parent, uint32_t child, VERTIGAL_SCENE_ARENA* arena)
{
    SceneNode* _child = NULL;
    SceneNode* _parent = NULL;
    SceneNode* _appendedNode = NULL;

    _appendedNode = getNodeByHandle(getArenaSlot(arena), arena);
    _child = getNodeByHandle(parent, arena);
    _parent = getNodeByHandle(parent, arena);

    for(uint8_t i = 0; i<4; i++)
    {


        if(_parent->children[i] == NULL)
        {   
            _appendedNode->nodeID = _child->nodeID;
            _appendedNode->parent = parent;
            _appendedNode->program = _child->program;
            _appendedNode->nodeID = _child->nodeID;
            memcpy(_appendedNode->name, _child->name, 128);
            
            _parent->children[i] = _appendedNode->nodeID;
            arena->tree->numNodes++;
        }   
    }
    
    return _appendedNode->nodeID;
}

void populateTree()
{
    return;   
}

void initSceneGraphArena(uint32_t numNodes, VERTIGAL_SCENE_ARENA* arena, VG_PLAYER_CAMERA* cam)
{   
    if(arena->initialized == true) 
        return;

    arena->nodePool = malloc(numNodes * sizeof(SceneNode) + sizeof(SceneRoot));
    arena->arenaSize = numNodes;
    arena->arenaUsed = 0;
    arena->root = getArenaSlot(arena);
    arena->arenaUsed +=1;
    arena->tree = malloc(sizeof(SceneTree));
    memcpy(&arena->tree->root.type.camera, cam, sizeof(VG_PLAYER_CAMERA));
    memset(arena->slotInUse, false, sizeof(arena->slotInUse));       

    //TODO: check allocations

    arena->initialized = true;

    if((arena->nodePool == NULL) || (arena->tree == NULL))
    {
        arena = NULL;
    }
    return;
}

static inline uint32_t getArenaSlot(VERTIGAL_SCENE_ARENA* arena)
{
    uint32_t i = 0;
    
    while (arena->slotInUse[i])
    {
        i++;
        if(i >= 128)
        {
            return 0;
        }
    }
    return i;
}

static inline SceneNode* getNodeByHandle(uint32_t handle, VERTIGAL_SCENE_ARENA* arena)
{
    return &arena->nodePool[handle];
}

/*
    TODO: 
    Make a stack for parsing by the renderer
*/

void createRenderStack(SceneStack* sceneStack, int32_t size)
{
    sceneStack = malloc(sizeof(sceneStack));

    if(sceneStack == NULL) return ;

    sceneStack->nodeIndex = malloc(sizeof(int32_t) * size);
    
    if (sceneStack->nodeIndex == NULL) return;
    
    return;
}

void increaseRenderStack(SceneStack* sceneStack)
{
    return;
}

void decreaseRenderStack(SceneStack* sceneStack)
{
    return;
}

void walkSceneTree()
{
    return;
}

void buildRenderStack(SceneTree* tree, SceneStack stack)
{
    /**
     * //TODO:
     *  - Parse the tree
     *  - Put the nodes to be rendered in a list
     *  - Send that list to the renderer 
     *  */ 

    return;
}