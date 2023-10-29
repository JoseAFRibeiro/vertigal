#include "glad/glad.h"
#include "vertigal/iofuncs.h"
#include "vertigal/glstrcuts.h"
#include <GLFW/glfw3.h>
#include <unistd.h>

#define INFO_LOG_SIZE 2048

GLuint compileShader(const char* path, GLenum shaderType)
{
    char* buffer;
    char iLog[INFO_LOG_SIZE];
    size_t size;
    GLuint shader;
    GLuint success;
    GLuint logSize;
    
    buffer = readFileToBuffer(&size, path);
    
    if(buffer == NULL)
        return 0;

    buffer[size + 1] = '\0';
    
    shader =  glCreateShader(shaderType);

    glShaderSource(shader, 1, &buffer, NULL);
    glCompileShader(shader);

    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logSize);
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

    
    if(success == GL_FALSE)
    {
        if(logSize > INFO_LOG_SIZE)
            warn("Shader compilation log is larger than buffer");

        glGetShaderInfoLog(shader, INFO_LOG_SIZE, NULL, iLog);

        error(iLog);
        free(buffer);
        return 0;
    }
    
    free(buffer);
    return shader;
}

GLuint compileShaderProgram(VG_shader_packet p)
{
    GLuint program;
    char iLog[INFO_LOG_SIZE];
    size_t size;
    GLuint success;
    GLuint logSize;

    uint8_t numShaders = p.numShaders;

    program = glCreateProgram();

    glAttachShader(program, p.fragment);
    glAttachShader(program, p.vertex);

    //TODO: add logic to attach other shaders

    glLinkProgram(program);

    glGetProgramiv(program, GL_INFO_LOG_LENGTH, &logSize);
    glGetProgramiv(program, GL_LINK_STATUS, &success);

    if(success == GL_FALSE)
    {
        if(logSize > INFO_LOG_SIZE)
            warn("Linking log is larger than buffer");

        glGetProgramInfoLog(program, INFO_LOG_SIZE, &logSize, iLog);
        glDeleteShader(p.fragment);
        glDeleteShader(p.vertex);
        glDeleteProgram(program);

        return 0;
    }

    glDeleteShader(p.fragment);
    glDeleteShader(p.vertex);

    return program;
}