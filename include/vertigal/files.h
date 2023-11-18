#ifndef FILES_H_
#define FILES_H_

#include <stdint.h>

typedef struct {
    char* buffer;
    size_t __cursor;
}file_buffer_t;

#endif 