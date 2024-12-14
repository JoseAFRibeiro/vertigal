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

typedef enum {
    GEOMETRIC_VERTEX,
    VERTEX_NORMAL,
    VERTEX_TEXTURE,
    FACE_INDEX,
    MATERIAL,
    LINE_ELEMENT,
    GROUP
}VG_ENUM_LINE_TYPE;

typedef enum{
    VERTEX_ONLY,
    VT_INDEX,
    VTN_INDEX,
    VN_INDEX
}VG_OBJ_FACE_TYPE;

typedef struct {
    VG_ENUM_LINE_TYPE lineType;
    uint32_t len;
    uint32_t offset;
}VG_OBJ_LINE_t;

typedef struct{
    size_t sizeOfArray;
    size_t currNumElements;
    size_t currSizeElements;
    size_t currPosition;
    uint32_t numVerts;
    uint32_t numFaces;
    uint32_t numTex;
    uint32_t numGroups;
    VG_OBJ_LINE_t* list; 
}VG_OBJ_ATTRIB_ARRAY_t;

uint8_t VG_InitLineAttribArray(VG_OBJ_ATTRIB_ARRAY_t* array, size_t initialSize);
uint8_t VG_arrayListSetElementAtIndex(VG_OBJ_ATTRIB_ARRAY_t** restrict array, size_t index, VG_OBJ_LINE_t* restrict value);
uint8_t VG_arrayListAddElement(VG_OBJ_ATTRIB_ARRAY_t** restrict array, VG_OBJ_LINE_t* restrict value);
void VG_arrayListFree(VG_OBJ_ATTRIB_ARRAY_t* array);
VG_3D_ENTITY* loadModelFromObj(const char* restrict path);


#endif 