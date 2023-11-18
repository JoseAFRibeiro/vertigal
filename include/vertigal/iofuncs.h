#ifndef IOFUNCS_H_
#define IOFUNCS_H_

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "files.h"

char* readFileToBuffer(size_t* size, const char* path);
void vg_warn(char* msg);
void vg_log(char* msg);
void vg_error(char*msg);
ssize_t VG_getline(char** restrict lineptr, size_t* restrict n, file_buffer_t* restrict fb, bool* isEOF);

#endif 