#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include "vertigal/models.h"
#include "vertigal/iofuncs.h"

/*void vertexHandler(const char* restrict line)
{
    if(line[1] == 'p')
    {
        return;
    }

    if(line[1] == 'n')
    {
        return;
    }


}

void parseLine(const char* restrict line, VG_3D_ENTITY* ent)
{
    switch (line[0])
    {
    case '#':
        break;
    case 'v':
        break;
    case 'g':
        break;
    default:
        break;
    }
}*/

void vertexToFloatArray(VG_3D_ENTITY *ent, char* restrict buffer, uint32_t vertexIndex)
{   
    uint8_t cursor = 0;
    uint8_t slice_begin;
    uint8_t slice_end;
    char tempBuffer[1024];

    for(int i = 0 ; ; i++)
    {

        if((buffer[cursor] >= '0') && (buffer[cursor] <= '9'))
        {
            slice_begin = cursor;

            while((buffer[cursor] != ' ') | (buffer[cursor] != '\n'))
            {
                cursor++;
            }

            slice_end = cursor;
            memcpy(tempBuffer, &buffer[slice_begin], slice_end - slice_begin);

            ent->vertexArray[vertexIndex].pos[i] = atof(tempBuffer);
            memset(tempBuffer, 0, sizeof(tempBuffer));

            if(buffer[cursor] == '\n')
                break;
        }

        cursor++;
    }
    
}

VG_3D_ENTITY secondPassParse(VG_3D_MODEL_ATTRIBUTES attrib, FILE* f)
{
    char* buffer;
    uint16_t compBuffer;
    size_t lineLen;
    ssize_t size;
    uint32_t vertIndex = 0;
    VG_3D_ENTITY ent;

    ent.vertexArray = malloc(sizeof(VG_3D_VERTEX) * attrib.numVertices);

    while(vertIndex < attrib.numVertices)
    {
        buffer = NULL;
        
        size = getline(&buffer, &lineLen, f);

        compBuffer = buffer[0];
        compBuffer =compBuffer << 8;
        compBuffer = compBuffer | buffer[1];

        switch (compBuffer)
        {
        case 0x7620:
            vertexToFloatArray(&ent, buffer, vertIndex);
            vertIndex++;
            break;
        case 0x766E:

            break;

        case 0x6620:

            break;
        
        default:
            break;
        }


        free(buffer);
        compBuffer = 0;
    }
}


VG_3D_MODEL_ATTRIBUTES firstPassParse(FILE* f)
{
    char* buffer;
    uint16_t compBuffer;

    size_t lineLen;
    ssize_t size;
    VG_3D_MODEL_ATTRIBUTES att = {0};
    
    while(!feof(f))
    {   
        buffer = NULL;
        
        size = getline(&buffer, &lineLen, f);

        compBuffer = buffer[0];
        compBuffer =compBuffer << 8;
        compBuffer = compBuffer | buffer[1];

        switch (compBuffer)
        {
        case 0x7620:
            att.numVertices++;
            break;
        case 0x766E:
            att.numNormals++;
            break;

        case 0x6620:
            att.numFaces++;
            break;
        
        default:
            break;
        }

        free(buffer);
        compBuffer = 0;
    }
    rewind(f);
    return att;
}

VG_3D_ENTITY loadModelFromObj(const char* path)
{
    char* buffer;
    size_t lineLen;
    ssize_t size;
    FILE* f;
    VG_3D_ENTITY entity;
    VG_3D_MODEL_ATTRIBUTES attrib;
    VG_3D_ENTITY ent;
    
    f = fopen(path, "rb");
    
        
    attrib = firstPassParse(f);
    ent = secondPassParse(attrib, f);

    return ent;
}