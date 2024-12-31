#include <stdint.h>
#include <malloc.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include "vertigal/arena.h"

static VERTIGAL_MODEL_ARENA arena = {0}; 

void initObjectArena(uint64_t initialSizeVertex, uint64_t initialSizeIndex)
{   
    if(arena.initialized == true) 
        return;

    VERTIGAL_MODEL_ARENA initArena = {0};
    
    initArena.sizeIndexes = initialSizeIndex;
    initArena.sizeVertices = initialSizeVertex;
    initArena.freeIndexes = initialSizeIndex;
    initArena.freeVertices = initialSizeVertex;
    initArena.initialized = true;

    initArena.indexes = malloc(sizeof(int32_t) * initialSizeIndex);
    initArena.vertices = malloc(sizeof(int32_t) * initialSizeVertex);

    arena = initArena;
    return;
}

void freeObjectArena()
{
    free(arena.indexes);
    free(arena.vertices);
    memset(&arena, 0, sizeof(VERTIGAL_MODEL_ARENA));
}

vertigal_handle objectArenaAddModel(vec3* vertexBuffer, uint32_t vBufferSize, int32_t* indexBuffer, uint32_t iBufferSize)
{
    VERTIGAL_ARENA_MODEL_IDENTIFIER* handle = NULL;
    VERTIGAL_ARENA_MODEL_IDENTIFIER* prevHandle = NULL;
    vertigal_handle returnHandle = 0;

    //find a free handle
    while(arena.modelHandlePool[returnHandle].allocated == true && returnHandle < 100)
        returnHandle++;

    //check if we have enough memory
    if(arena.freeIndexes < iBufferSize)
    {   
        printf("Allocating more space for indices\n");
        arena.indexes = realloc(arena.indexes, (arena.sizeIndexes + iBufferSize) * sizeof(int32_t) * 3);
        arena.sizeIndexes += iBufferSize;
        arena.freeIndexes += iBufferSize;
    }

    if(arena.freeVertices < vBufferSize)
    {
        printf("Allocating more space for vertices\n");
        arena.vertices = realloc(arena.vertices, (vBufferSize + arena.sizeVertices) * sizeof(vec3));
        arena.sizeVertices += vBufferSize;
        arena.freeVertices += vBufferSize;
    }

    //fill up the structure revcovered by the handle
    handle = &arena.modelHandlePool[returnHandle];
    
    if(handle->allocated == true)
        return -1;

    handle->allocated = true;
    handle->indexLen = iBufferSize;
    handle->verticesSLen = vBufferSize;

    //if it is our first allocation
    if(returnHandle == 0)
    {
        handle->indexStart = 0;
        handle->verticesStart = 0;
    } else //all other allocations
    {
        prevHandle = &arena.modelHandlePool[returnHandle - 1];

        handle->indexStart = prevHandle->indexStart + prevHandle->indexLen + 1;
        handle->verticesStart = prevHandle->verticesStart + prevHandle->verticesSLen;

        /*for (uint32_t indexCursor = 0; indexCursor < iBufferSize; indexCursor++)
        {
            indexBuffer[indexCursor] += handle->verticesStart;
        }*/
        
    }

    memcpy(&arena.indexes[handle->indexStart],indexBuffer, iBufferSize * sizeof(int32_t));
    memcpy(&arena.vertices[handle->verticesStart],vertexBuffer, vBufferSize * sizeof(vec3));

    arena.freeIndexes -= iBufferSize;
    arena.freeVertices -= vBufferSize;

    return returnHandle;
}

VERTIGAL_MODEL_ARENA* getArenaptr()
{
    return &arena;
}