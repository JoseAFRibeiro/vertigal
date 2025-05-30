#ifndef GLSTRCUTS_H_
#define GLSTRCUTS_H_

#include "glad/glad.h"

typedef struct {
    GLuint fragment;
    GLuint vertex;
    GLuint geometry;
    uint8_t numShaders;
}VG_shader_packet;

#endif 