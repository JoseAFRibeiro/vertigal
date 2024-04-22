#ifndef IOFUNCS_H_
#define IOFUNCS_H_

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>
#include <sys/types.h>
#include "files.h"

char* readFileToBuffer(size_t* size, const char* path);
void vg_warn(char* msg);
void vg_log(char* msg);
void vg_error(char*msg);
void vg_printArrayVertex(float* ptr, size_t numElements);
ssize_t VG_getline(char** restrict lineptr, size_t* restrict lineLength, file_buffer_t* restrict fb, bool* isEOF);

#endif 