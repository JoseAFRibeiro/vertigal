#include <malloc.h>
#include "vertigal/scene.h"
#include "vertigal/arena.h"
#include "vertigal/models.h"


static SceneTree* tree;
static VERTIGAL_MODEL_ARENA* arena;

SceneTree* createSceneTree()
{
    
    SceneNode* mainMenu;
    SceneNode* options;    
    SceneNode* game;    

    tree = malloc(sizeof(SceneTree));

    mainMenu = malloc(sizeof(SceneNode) * 5);
    
    options = &mainMenu[1];
    game = &mainMenu[2];

    tree->root = mainMenu;
    mainMenu->children = &mainMenu[4];

    options->parent = mainMenu;
    game->parent = mainMenu;

    mainMenu->children[0] = options;
    return tree;
}

void scene1()
{

    size_t sceneVertexSize = 0;
    size_t sceneVertexStart = 0;
    size_t sceneIndexSize = 0;
    size_t sceneIndexStart = 0;

    vertigal_handle cube = loadModelFromObj("./res./cube.obj");
    
    sceneVertexSize +=  arena->modelHandlePool[cube].verticesLen;
    sceneIndexSize +=  arena->modelHandlePool[cube].indexLen;
    sceneVertexStart = arena->modelHandlePool[cube].verticesStart;
    sceneIndexStart = arena->modelHandlePool[cube].indexStart;

    vertigal_handle cow = loadModelFromObj("./res./cow.obj");

    sceneVertexSize +=  arena->modelHandlePool[cow].verticesLen;
    sceneIndexSize +=  arena->modelHandlePool[cow].indexLen;

    tree->root->parent = NULL;
    tree->root->indicesStart = sceneIndexStart;
    tree->root->verticesStart = sceneVertexStart;
    tree->root->indicesLen = sceneIndexSize;
    tree->root->verticesLen = sceneVertexSize;

    return;
}

void scene2(SceneNode* currentNode)
{    
    size_t sceneVertexSize = 0;
    size_t sceneVertexStart = 0;
    size_t sceneIndexSize = 0;
    size_t sceneIndexStart = 0;

    vertigal_handle cube = loadModelFromObj("./res./cube.obj");
    
    sceneVertexSize +=  arena->modelHandlePool[cube].verticesLen;
    sceneIndexSize +=  arena->modelHandlePool[cube].indexLen;
    sceneVertexStart = arena->modelHandlePool[cube].verticesStart;
    sceneIndexStart = arena->modelHandlePool[cube].indexStart;

    vertigal_handle teapot = loadModelFromObj("./res./teapot.obj");

    sceneVertexSize +=  arena->modelHandlePool[teapot].verticesLen;
    sceneIndexSize +=  arena->modelHandlePool[teapot].indexLen;

    currentNode->parent = tree->root;
    currentNode->indicesStart = sceneIndexStart;
    currentNode->verticesStart = sceneVertexStart;
    currentNode->indicesLen = sceneIndexSize;
    currentNode->verticesLen = sceneVertexSize;

    tree->root->children[0] = currentNode;

    return;
}

void populateTree()
{
    
    initObjectArena(1000, 1000);
    arena = getArenaptr();
    scene1();
    scene2(&tree->root->children[0]);

}