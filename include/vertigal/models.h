#ifndef VERTIGAL_MODELS_H_
#define VERTIGAL_MODELS_H_
#include <stdint.h>
#include <cglm/vec3.h>
#include <cglm/vec2.h>
#include <cglm/ivec3.h>

#define VG_OBJ_LINE_SIZE sizeof(VG_OBJ_LINE_t)
#define OBJ_VERTEX_ID 0x2076
#define OBJ_TEX_ID 0x6E76
#define OBJ_FACE_ID 0x2066
#define OBJ_GROUP_ID_1 0x670A
#define OBJ_GROUP_ID_2 0x2067

typedef struct
{
    uint32_t groupOffset[256];
    uint32_t groupLen[256];
    uint32_t numGroups;
    uint32_t currGroup;
    char groupName[255][256];
}VG_3D_MODEL_GROUPS;


typedef struct{
    uint32_t numVertices;
    uint32_t numFaces;
    uint32_t numNormals;
}VG_3D_MODEL_ATTRIBUTES;

typedef struct{
    vec3* vertexArray;
    int32_t* faceIndices;
    VG_3D_MODEL_ATTRIBUTES attribs;
    VG_3D_MODEL_GROUPS groups;
}VG_3D_ENTITY;

VG_3D_ENTITY* loadModelFromObj(const char* restrict path);


#endif 