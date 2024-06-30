#version 450 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec3 aUV;
out vec3 vertexPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;


out vec2 TexCoords;

void main()
{
    gl_Position = projection * view * model * vec4(aPos.x, aPos.y, aPos.z, 1.0);
    vertexPos = vec3(aPos.x, aPos.y, aPos.z);
}   