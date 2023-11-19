#include <stdlib.h>
#include <stdio.h>

char* readFileToBuffer(size_t* size, const char* path)
{
    FILE* f;
    char* buffer;

    f = fopen(path, "rb");
    
    if(!f)
        return NULL;

    if(fseek(f, 0, SEEK_END))
    {
        fclose(f);
        return NULL;
    }

    (*size) = ftell(f);

    if( *size == -1)
    {
        fclose(f);
        return NULL; //TODO: Check error?
    }    
    
    buffer = malloc(*size + 2);

    if(!buffer)
    {
        fclose(f);
        return NULL;    
    }    

    rewind(f);
    if(fread((void*) buffer, sizeof(char), *size, f) != *size)
    {
        free(buffer);
        fclose(f);
        return NULL;
    }

    fclose(f);
    buffer[*size] = '\0';
    return buffer;
}