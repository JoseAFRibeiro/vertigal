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
    arena->root = getArenaSlot(arena);
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


        if(_parent->children[i] == 0)
        {   
            _appendedNode->nodeID = _child->nodeID;
            _appendedNode->parent = parent;
            _appendedNode->program = _child->program;
            _appendedNode->nodeID = _child->nodeID;
            memcpy(_appendedNode->name, _child->name, 128);
            
            _parent->children[i] = _appendedNode->nodeID;
            arena->tree->numNodes++;
            break;
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
    memset(arena->nodePool, 0,numNodes * sizeof(SceneNode) + sizeof(SceneRoot));
    arena->arenaSize = numNodes;
    arena->arenaUsed = 0;
    arena->root = getArenaSlot(arena);
    arena->arenaUsed +=1;
    arena->tree = malloc(sizeof(SceneTree));
    memset(arena->tree, 0, sizeof(SceneTree));
    memcpy(&arena->tree->root.type.camera, cam, sizeof(VG_PLAYER_CAMERA));
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
    arena->slotInUse[i] = true;
    return i;
}

static inline SceneNode* getNodeByHandle(uint32_t handle, VERTIGAL_SCENE_ARENA* arena)
{
    return &(*arena).nodePool[handle];
}

/*
    TODO: 
    Make a stack for parsing by the renderer
*/

void createRenderStack(SceneStack** restrict sceneStack, int32_t size)
{
    *sceneStack = calloc(1, sizeof(SceneStack));

    if(sceneStack == NULL) return ;

    (*sceneStack)->nodeIndex = calloc( size, sizeof(int32_t));
    (*sceneStack)->nodeFaceIndexStart = calloc(size, sizeof(int32_t));
    (*sceneStack)->nodeFaceIndexCount = calloc(size, sizeof(int32_t));
    
    if ((*sceneStack)->nodeIndex == NULL) return;
    if ((*sceneStack)->nodeFaceIndexStart == NULL) return;
    if ((*sceneStack)->nodeFaceIndexCount == NULL) return;

    
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

void addToStack(SceneStack* stack, SceneNode node, VERTIGAL_MODEL_ARENA* modelArena)
{
    vertigal_handle modelArenaHandle = node.modelArenaID;
    uint32_t lenFaces = 0;
    uint32_t startFaces = 0;

    lenFaces = modelArena->modelHandlePool[modelArenaHandle].indexLen;
    startFaces = modelArena->modelHandlePool[modelArenaHandle].indexStart;

    stack->nodeFaceIndexCount[stack->nodes] = lenFaces;
    stack->nodeFaceIndexStart[stack->nodes] = startFaces; 
    stack->nodes++;
    return;
}

void walkSceneTree(SceneNode node, uint16_t count, VERTIGAL_SCENE_ARENA* arena, SceneStack* stack, VERTIGAL_MODEL_ARENA* modelArena)
{   

    for(uint8_t i = 0; i <= 3; i++)
    {
        if(node.children[i] > 0)
        {
            walkSceneTree(*getNodeByHandle(node.modelArenaID, arena), ++count, arena, stack, modelArena);
        } else{
            addToStack(stack, node, modelArena);            
        }
    }

    return;
}

void buildRenderStack(SceneTree* tree, SceneStack* stack, VERTIGAL_SCENE_ARENA* arena, VERTIGAL_MODEL_ARENA* modelArena)
{
    /**
     * //TODO:
     *  - Parse the tree
     *  - Put the nodes to be rendered in a list
     *  - Send that list to the renderer 
     *  */ 
    
    for(uint8_t i = 0; i <= 3; i++)
    {
        walkSceneTree(*getNodeByHandle(tree->root.children[i], arena), 0, arena, stack, modelArena);
    }    
    
    return;
}