#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stddef.h>
#include "vertigal/models.h"
#include "vertigal/iofuncs.h"

uint8_t retrieveModelMetadata(file_buffer_t* buffer, VG_OBJ_ATTRIB_ARRAY_t* restrict attribs)
{
    char* lnBuffer;
    uint16_t lnIdentifier;
    uint8_t result;
    size_t lnCursor;
    size_t* lineStartOffset = &buffer->__cursor;
    bool quit = false;


    char temp[100] = {0};
    int counter = 1;
    do
    {
        lnCursor = 0;
    
        do
        {
            lnCursor++;
        } while (!(buffer->buffer[ *lineStartOffset + lnCursor] == '\n' || buffer->buffer[*lineStartOffset + lnCursor] == '\0'));
        
        lnBuffer = malloc(sizeof(char) * lnCursor + 1);
        
        if(lnBuffer == NULL) return 1;
        if(buffer->buffer[lnCursor + *lineStartOffset] == '\0') quit = true;
        
        memcpy(lnBuffer, &buffer->buffer[*lineStartOffset], lnCursor);
        memcpy(&lnIdentifier, &buffer->buffer[*lineStartOffset], sizeof(uint16_t));

        VG_OBJ_LINE_t lineObj = {
            .len = lnCursor,
            .offset = *lineStartOffset
        };

        switch (lnIdentifier)
        {
        case OBJ_VERTEX_ID :
            lineObj.lineType = GEOMETRIC_VERTEX;
            vg_log("Vertex");
            break;
        
        default:
            lineObj.lineType = VERTEX_NORMAL;
            break;
        }

        result = VG_arrayListAddElement(attribs, &lineObj);
        *lineStartOffset += lnCursor + 1;
        free(lnBuffer);
        lnBuffer = NULL;

        sprintf(temp, "Still here %d", counter);
        vg_log(temp);
        counter++;
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