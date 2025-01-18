#ifndef VERTIGAL_ARENA_H
#define VERTIGAL_ARENA_H

#define NUM_MAX_MODELS 100

#include <stdint.h>
#include <stdbool.h>
#include <cglm/vec3.h>

typedef int32_t vertigal_handle;

typedef struct {
    int32_t indexStart;
    int32_t indexLen;
    int32_t verticesStart;
    int32_t verticesSLen;
    bool allocated;
}VERTIGAL_ARENA_MODEL_IDENTIFIER;

typedef struct
{
    //allocate a pool of memory for vertices, another for indexes and another for model "handles"
    VERTIGAL_ARENA_MODEL_IDENTIFIER modelHandlePool[NUM_MAX_MODELS];
    vec3* vertices;
    int32_t* indexes;
    uint64_t sizeVertices;
    uint64_t sizeIndexes;
    uint64_t freeIndexes;
    uint64_t freeVertices;
    bool initialized;
} VERTIGAL_MODEL_ARENA;

vertigal_handle objectArenaAddModel(vec3* vertexBuffer, uint32_t vBufferSize, int32_t* indexBuffer, uint32_t iBufferSize);
void freeObjectArena();
void initObjectArena(uint64_t initialSizeVertex, uint64_t initialSizeIndex);
VERTIGAL_MODEL_ARENA* getArenaptr();

#endif