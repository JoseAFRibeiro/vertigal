#ifndef IOFUNCS_H_
#define IOFUNCS_H_

#include <stdlib.h>

char* readFileToBuffer(size_t* size, const char* path);
void vg_warn(char* msg);
void vg_log(char* msg);
void vg_error(char*msg);


#endif 