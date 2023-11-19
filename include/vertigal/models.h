#ifndef VERTIGAL_MODELS_H_
#define VERTIGAL_MODELS_H_
#include <stdint.h>
#include <cglm/vec3.h>
#include <cglm/vec2.h>


typedef struct {
    vec3 pos;
    vec3 normal;
    vec2 uv;
}VG_3D_VERTEX;

typedef struct{
    VG_3D_VERTEX* vertexArray;
}VG_3D_ENTITY;

typedef struct{
    uint32_t numVertices;
    uint32_t numFaces;
    uint32_t numNormals;
}VG_3D_MODEL_ATTRIBUTES;

VG_3D_ENTITY loadModelFromObj(const char* restrict path);

#endif 