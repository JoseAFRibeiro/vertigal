#version 450 core

out vec4 FragColor;

uniform vec3 objectColor;
uniform vec3 lightColor;

in vec3 FaceNormal;

void main()
{
    FragColor = vec4(lightColor * objectColor, 1.0f);
}