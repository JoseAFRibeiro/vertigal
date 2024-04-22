#include <stdio.h>

#define TEXT_RED "\033[1;31m"
#define TEXT_GREEN "\033[1;32m"
#define TEXT_YELLOW "\033[1;33m"
#define TEXT_RESET "\033[0m"

void vg_warn(char* msg)
{
    fprintf(stderr, "%s WARNING %s: %s\n", TEXT_YELLOW, TEXT_RESET, msg);
    return;
}

void vg_log(char* msg)
{
    fprintf(stderr, "%s LOG %s: %s\n", TEXT_GREEN, TEXT_RESET, msg);
    return;
}

void vg_error(char*msg)
{
    fprintf(stderr, "%s ERROR %s: %s\n", TEXT_RED, TEXT_RESET, msg);
    return;
}

void vg_printArrayVertex(float* ptr, size_t numElements)
{
    for(size_t i = 0; i < numElements * 3; i+=4)
    {
        fprintf(stderr, "x: %f | y: %f | z: %f\n", ptr[i], ptr[i+1],ptr[i+2]);
    }
}   