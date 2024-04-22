#version 450 core

in vec3 vertexPos;

out vec4 FragColor;

void main()
{
    FragColor = vec4(vertexPos.x, vertexPos.y, vertexPos.z, 1.0f);
}