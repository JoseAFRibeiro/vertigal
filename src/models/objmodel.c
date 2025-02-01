#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>
#include <malloc.h>
#include "vertigal/models.h"
#include "vertigal/iofuncs.h"
#include "vertigal/arena.h"

#define NUM_INDEX_PER_FACE 30

static int numV = 0;
static int32_t numGroup = -1;

void vertexHandler(float* results, const char* restrict line)
{
    char floatString[1024] = {0};
    int32_t stringCursor = 0;
    int32_t vertexCursor = 0;
    int32_t resultCursor = 0;
    //TODO: switch most comparisons with a single if < to - or other character
    while(line[vertexCursor] != '-' && (line[vertexCursor] < '0' || line[vertexCursor] > '9'  ))
        vertexCursor++;
    
    vertexCursor--;

    while(line[vertexCursor] != '\n' && line[vertexCursor] !='\r' && line[vertexCursor] !='\0')
    {
        
        vertexCursor++;

        while(line[vertexCursor] !='\n' && line[vertexCursor] !=' ' && line[vertexCursor] !='\r' && line[vertexCursor] !='\0')
        {
            floatString[stringCursor] = line[vertexCursor];
            stringCursor++;
            vertexCursor++;
        }
        
        results[resultCursor]  = strtof(floatString, &floatString[stringCursor]);
        memset(floatString, 0, 1024);
        stringCursor = 0;
        resultCursor++;
    }

    return;
}

void faceHandler(int32_t* results, const char* restrict line)
{   
    int32_t faceCursor = 0;
    int32_t resultCursor = 0;
    int32_t stringCursor = 0;
    char indexString[1024] = {0};

    while(line[faceCursor] < '-' || line[faceCursor] > '9')
        faceCursor++;

    faceCursor--;

    while(line[faceCursor] != '\0' && line[faceCursor] != '\r' && line[faceCursor] != '\n')
    {   

        while (line[faceCursor] < '0' || line[faceCursor] > '9') 
        {
            faceCursor++;
        }
        

        while(line[faceCursor] != '/' && line[faceCursor] != ' ' && line[faceCursor] != '\r' && line[faceCursor] != '\0' )
        {
            indexString[stringCursor] = line[faceCursor];

            faceCursor++;
            stringCursor++;
        }

        results[resultCursor] = strtol(indexString, &indexString[stringCursor], 10);
        resultCursor++;
        stringCursor = 0;
        memset(indexString, 0, 1024);

        if(line[faceCursor] == '/')
        {
            while(line[faceCursor] != ' ' && line[faceCursor] != '\0' && line[faceCursor] != '\r')
                faceCursor++;
        }
    }

    return;
}

VG_3D_ENTITY* modelLineParser(file_buffer_t file)
{
    VG_3D_ENTITY *ent =  NULL;
    int32_t lineCount = 0;
    int32_t cursor = 0;
    int32_t vertCount = 0;
    int32_t indexCount = 0;
    char lineBuffer[1024] = {0};


    ent = malloc(sizeof(VG_3D_ENTITY));
    //wasteful, fix later
    ent->vertexArray = malloc(500000 * sizeof(vec3));
    ent->faceIndices = malloc(10000000 * (sizeof(int32_t) * 3));

    while(file.buffer[cursor] != '\0')
    {
        if(file.buffer[cursor] == '\n')
            lineCount++;
        
        cursor++;
    }
    
    cursor = 0;

    int repeat = 0;

    for (int32_t line = 0; line <= lineCount; line++)
    {

        uint32_t lineStartOffset = 0;
        int32_t indexOut[3] = {0};
        float vertexOut[3] = {0};
        while(file.buffer[cursor + lineStartOffset] != '\n' && file.buffer[cursor + lineStartOffset] != '\0')
            lineStartOffset++;
        memcpy(lineBuffer, &file.buffer[cursor], lineStartOffset);


        /*
            Do stuff with the line
        */

       switch (lineBuffer[0])
        {
            case 'v':

                    if(lineBuffer[1] == 'n')
                {
                    break;
                }
                
                vertexHandler(vertexOut, lineBuffer);
                ent->vertexArray[vertCount][0] = vertexOut[0];
                ent->vertexArray[vertCount][1] = vertexOut[1];
                ent->vertexArray[vertCount][2] = vertexOut[2];
                vertCount++;
                break;
            case 'f':
                faceHandler(indexOut, lineBuffer);
                repeat++;
                printf("%d\n", repeat);
                ent->faceIndices[indexCount] = indexOut[0] - 1;
                indexCount++;
                ent->faceIndices[indexCount] = indexOut[1] - 1 ;
                indexCount++;
                ent->faceIndices[indexCount] = indexOut[2] - 1;
                indexCount++;

                break;
            default:
                break;
        }

        cursor += lineStartOffset + 1;
        memset(lineBuffer, 0, 1024);
    }
    ent->attribs.numVertices = vertCount;
    ent->attribs.numFaces = indexCount;

    return ent;

}

VG_3D_ENTITY* loadModelFromObj(const char* restrict path)
{
    size_t bufferLen;
    uint8_t result;
    VG_3D_ENTITY* entptr;
    file_buffer_t fb;

    numV = 0;
    fb.__cursor = 0;
    fb.buffer = readFileToBuffer(&bufferLen, path);
    entptr = modelLineParser(fb);

    initObjectArena(500, 500);

    objectArenaAddModel(entptr->vertexArray, entptr->attribs.numVertices, entptr->faceIndices, entptr->attribs.numFaces);
    
    return entptr;
}