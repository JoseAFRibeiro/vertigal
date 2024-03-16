#include <stdlib.h> 
#include <stdint.h> 
#include <malloc.h>
#include <string.h>

#include "vertigal/models.h"

uint8_t VG_InitLineAttribArray(VG_OBJ_ATTRIB_ARRAY_t* restrict array, size_t initialSize)
{
    if(array == NULL) return 5;

    array->list = calloc(initialSize, VG_OBJ_LINE_SIZE);

    if(array->list == NULL) return 1;

    array->currNumElements = 0;
    array->sizeOfArray = initialSize;
    array->currPosition = 0;
    return 0;
}

void VG_arrayListFree(VG_OBJ_ATTRIB_ARRAY_t* restrict array)
{
    free(array->list);
    memset(array, 0, VG_OBJ_LINE_SIZE);
}

uint8_t VG_arrayListSetElementAtIndex(VG_OBJ_ATTRIB_ARRAY_t* restrict array, size_t index, VG_OBJ_LINE_t* restrict value)
{
    if(array == NULL) return 6;
    if(array->list == NULL) return 5;
    if(value == NULL) return 4;
    
    if(index >= array->sizeOfArray / VG_OBJ_LINE_SIZE)
    {   
        size_t newArraySize = array->sizeOfArray + (VG_OBJ_LINE_SIZE * (index + 4));
        array->list = realloc(array->list, newArraySize);
        
        if(array->list == NULL) return 7;

        array->sizeOfArray = newArraySize;
        array->currSizeElements = newArraySize  / VG_OBJ_LINE_SIZE;
    }

    memcpy(&array->list[index], value, sizeof(VG_OBJ_LINE_t));
    return 0;
}

uint8_t VG_arrayListAddElement(VG_OBJ_ATTRIB_ARRAY_t* restrict array, VG_OBJ_LINE_t* restrict value)
{
    if(array == NULL) return 6;
    if(array->list == NULL) return 5;
    if(value == NULL) return 4;
    
    if(array->currPosition < array->sizeOfArray)
    {
        memcpy(&array->list[array->currPosition], value, sizeof(VG_OBJ_LINE_t));
        array->currPosition++;
    } else if(array->currPosition >= array->sizeOfArray) 
    {
        size_t newArraySize = array->sizeOfArray + 10;
        array->list = realloc(array->list, newArraySize * VG_OBJ_LINE_SIZE);

        if(array->list == NULL ) return 7;
        
        array->sizeOfArray = newArraySize;
        memcpy(&array->list[array->currPosition], value, sizeof(VG_OBJ_LINE_t));
        array->currPosition++;
    }

    return 0;
}
