#ifndef VERTIGAL_MODELS_H_
#define VERTIGAL_MODELS_H_
#include <stdint.h>
#include <cglm/vec3.h>
#include <cglm/vec2.h>

#define VG_OBJ_LINE_SIZE sizeof(VG_OBJ_LINE_t)
#define OBJ_VERTEX_ID 0x2076
#define OBJ_TEX_ID 0x6E76
#define OBJ_FACE_ID 0x2066

typedef struct {
    vec3 pos;
    vec3 normal;
    vec2 uv;
}VG_3D_VERTEX;

typedef struct{
    uint32_t numVertices;
    uint32_t numFaces;
    uint32_t numNormals;
}VG_3D_MODEL_ATTRIBUTES;

typedef struct{
    VG_3D_VERTEX* vertexArray;
    VG_3D_MODEL_ATTRIBUTES attribs;
    int32_t* faceIndices;
}VG_3D_ENTITY;

typedef enum {
    GEOMETRIC_VERTEX,
    VERTEX_NORMAL,
    VERTEX_TEXTURE,
    FACE_INDEX,
    MATERIAL,
    LINE_ELEMENT
}VG_ENUM_LINE_TYPE;

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
    VG_OBJ_LINE_t* list; 
}VG_OBJ_ATTRIB_ARRAY_t;

uint8_t VG_InitLineAttribArray(VG_OBJ_ATTRIB_ARRAY_t* array, size_t initialSize);
uint8_t VG_arrayListSetElementAtIndex(VG_OBJ_ATTRIB_ARRAY_t* restrict array, size_t index, VG_OBJ_LINE_t* restrict value);
uint8_t VG_arrayListAddElement(VG_OBJ_ATTRIB_ARRAY_t** restrict array, VG_OBJ_LINE_t* restrict value);
void VG_arrayListFree(VG_OBJ_ATTRIB_ARRAY_t* array);


VG_3D_ENTITY* loadModelFromObj(const char* restrict path);


#endif 