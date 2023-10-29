#ifndef IOFUNCS_H_
#define IOFUNCS_H_

#include <stdlib.h>

char* readFileToBuffer(size_t* size, const char* path);
void warn(char* msg);
void log(char* msg);
void error(char*msg);


#endif 