#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>
#include <malloc.h>
#include "vertigal/models.h"
#include "vertigal/iofuncs.h"

int numV = 0;

uint8_t vertexFaceHandeler(file_buffer_t* restrict buffer, size_t lineLen,uint32_t offset, 
                            int32_t* vertexFaceIndices)
{   
    //+3 to jump the first character + 2 follwing spaces
    uint32_t cursor = offset + 3;
    uint32_t bufferCursor = 0;
    char tempBuffer1[200] = {0};
    char tempBuffer2[200] = {0};
    char tempBuffer3[200] = {0};
    char* bufferLen;
    int32_t faceIndex = 0;

    while((cursor - offset) <= lineLen)
    {
        //loop first 
        while((buffer->buffer[cursor] >= '0' && buffer->buffer[cursor] <= '9') && buffer->buffer[cursor] != '-')
        {     
            tempBuffer1[bufferCursor] = buffer->buffer[cursor];
            bufferCursor++;
            cursor++; 
        }
        
        vertexFaceIndices[faceIndex] = strtol(tempBuffer1, &bufferLen, 10);
        memset(tempBuffer1, 0, sizeof(tempBuffer1));
        faceIndex++;
        cursor++;
        bufferCursor = 0;

        while((buffer->buffer[cursor] >= '0' && buffer->buffer[cursor] <= '9') && buffer->buffer[cursor] != '-')
        {     
            tempBuffer2[bufferCursor] = buffer->buffer[cursor];
            bufferCursor++;
            cursor++; 
        }

        cursor++;

        while((buffer->buffer[cursor] >= '0' && buffer->buffer[cursor] <= '9') && buffer->buffer[cursor] != '-')
        {     
            tempBuffer3[bufferCursor] = buffer->buffer[cursor];
            bufferCursor++;
            cursor++; 
        }

        cursor += 2;

    }

}

//TODO: handle optional W values, use len for optimisations -> use len over endline checks?
uint8_t vertexHandeler(file_buffer_t* restrict buffer, uint32_t len, uint32_t offset, vec3* vector)
{
    uint32_t bufferCursor;
    uint32_t cursor = offset;
    uint32_t posIndex = 0;
    char tempBuffer[200] = {0};
    char *bufferLen;
    while(true)
    {
        if((buffer->buffer[cursor] >= '0') && (buffer->buffer[cursor] <= '9'))
        {
            bufferCursor = 0;

            while(true)
            {   
                if(buffer->buffer[cursor] == ' ')   break;
                if(buffer->buffer[cursor] == '\n')  break;
                if(buffer->buffer[cursor] == '\r')  break;
                tempBuffer[bufferCursor] = buffer->buffer[cursor];
                cursor++;
                bufferCursor++;
            }

            double temp = (float) strtod(tempBuffer, &bufferLen);
            (*vector)[posIndex] = temp;

            memset(tempBuffer, 0, sizeof(tempBuffer));
            posIndex++;
            
        }

        if(buffer->buffer[cursor] == '\n')
            break;
        
        cursor++;
    }
    
    return 1;
}

uint8_t retrieveModelMetadata(file_buffer_t* buffer, VG_OBJ_ATTRIB_ARRAY_t* attribs)
{
    char* lnBuffer;
    uint16_t lnIdentifier;
    uint8_t result;
    size_t lnCursor;
    size_t* lineStartOffset = &buffer->__cursor;
    bool quit = false;
    VG_OBJ_LINE_t lineObj = {0};

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

        lineObj.len = lnCursor;
        lineObj.offset = *lineStartOffset;

        switch (lnIdentifier)
        {
            case OBJ_VERTEX_ID :
                lineObj.lineType = GEOMETRIC_VERTEX;
                attribs->numVerts++;
                result = VG_arrayListAddElement(&attribs, &lineObj);
                break;
            case OBJ_TEX_ID:
                lineObj.lineType = VERTEX_TEXTURE;
                attribs->numTex++;
                result = VG_arrayListAddElement(&attribs, &lineObj);
                break;            
            case OBJ_FACE_ID:
                lineObj.lineType = FACE_INDEX;
                attribs->numFaces++;
                result = VG_arrayListAddElement(&attribs, &lineObj);
                break;        
            default:
            break;
        }

        if(result != 0)
        {
            char errorBuffer[100] = {0};
            sprintf(errorBuffer, "Error: %d", result); 
            vg_error(errorBuffer);
            return result;
        }

        *lineStartOffset += lnCursor + 1;
        free(lnBuffer);
        lnBuffer = NULL;
    } while (!quit);
    
    return 0;
}

uint8_t objToVG3DEntity(file_buffer_t* buffer, VG_OBJ_ATTRIB_ARRAY_t* attribs, VG_3D_ENTITY *ent)
{
    uint32_t currentVertexIndex = 0;
    uint32_t faceIndex = 0;
    ent->attribs.numVertices = attribs->numVerts;
    ent->attribs.numFaces = attribs->numFaces;
    ent->vertexArray = malloc(attribs->numVerts * sizeof(vec3));
    ent->faceIndices = malloc((attribs->numFaces * sizeof(int32_t)) * 3);
    
    if((ent->vertexArray == NULL) || (ent->faceIndices == NULL))
        return 1;

    for(uint32_t i = 0; i < attribs->currPosition; i++)
    {
        uint32_t lineLen = attribs->list[i].len;
        uint32_t lineOffset = attribs->list[i]. offset;
        vec3 tempVec = {0};
        switch(attribs->list[i].lineType)
        {
            case GEOMETRIC_VERTEX:
                vertexHandeler(buffer, lineLen, lineOffset, &tempVec);
                ent->vertexArray[currentVertexIndex][0] = tempVec[0]; 
                ent->vertexArray[currentVertexIndex][1] = tempVec[1]; 
                ent->vertexArray[currentVertexIndex][2] = tempVec[2];
                currentVertexIndex += 1; 
                break;
            case FACE_INDEX:
                int32_t arr[3] = {0};
                vertexFaceHandeler(buffer, attribs->list[i].len,lineOffset, arr);
                ent->faceIndices[faceIndex] = arr[0];
                ent->faceIndices[faceIndex+1] = arr[1];
                ent->faceIndices[faceIndex+2] = arr[2];
                faceIndex+=3;
                break;
            default:
                break;
        }
    }
    return 0;
}   

VG_3D_ENTITY* loadModelFromObj(const char* restrict path)
{
    size_t bufferLen;
    uint8_t result;
    VG_3D_ENTITY* entptr;
    file_buffer_t fb;
    VG_OBJ_ATTRIB_ARRAY_t attribArray = {0};

    fb.__cursor = 0;
    fb.buffer = readFileToBuffer(&bufferLen, path);

    if(fb.buffer == NULL) return NULL;

    result = VG_InitLineAttribArray(&attribArray, 10);
    if(result != 0) return NULL;

    result = retrieveModelMetadata(&fb, &attribArray);
    if(result != 0) return NULL;

    entptr = malloc(sizeof(VG_3D_ENTITY));
    objToVG3DEntity(&fb, &attribArray, entptr);

    return entptr;
}