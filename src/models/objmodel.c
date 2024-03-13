#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stddef.h>
#include "vertigal/models.h"
#include "vertigal/iofuncs.h"

uint8_t retrieveModelMetadata(file_buffer_t* buffer, VG_OBJ_ATTRIB_ARRAY_t* restrict attribs)
{
    char* lineBuffer;
    bool quit = false;
    ssize_t lineSize;
    size_t lineLength;
    size_t offsetTracker;
    size_t index;
    VG_ENUM_LINE_TYPE lineType;
    uint16_t lineIdentifier;
    uint8_t result;
    offsetTracker = 0;

    do
    {
        lineSize = VG_getline(&lineBuffer, &lineLength, buffer, &quit);
        lineIdentifier = (uint16_t *) buffer->buffer[0];

        VG_OBJ_LINE_t lineObj = {
            .len = lineSize,
            .offset = offsetTracker
        };

        switch (lineIdentifier)
        {
        case OBJ_VERTEX_ID :
            lineObj.lineType = GEOMETRIC_VERTEX;
            break;
        
        default:
            break;
        }
        result = VG_arrayListSetElementAtIndex(attribs, index, &lineObj);
        offsetTracker += lineSize + 1;
    } while (!quit);
    
}

VG_3D_ENTITY* loadModelFromObj(const char* restrict path)
{
    char* buffer;
    uint8_t result;
    size_t lineLen;
    ssize_t size;
    VG_OBJ_ATTRIB_ARRAY_t attribArray;
    VG_3D_MODEL_ATTRIBUTES attrib;
    VG_3D_ENTITY ent;
    VG_3D_ENTITY entity;
    VG_3D_ENTITY* entptr;

    file_buffer_t fb;

    fb.__cursor = 0;
    fb.buffer = readFileToBuffer(&lineLen, path);

    if(fb.buffer == NULL) return NULL;

    VG_InitLineAttribArray(&attribArray, 10);
    retrieveModelMetadata(&fb, &attribArray);

    return entptr;
}