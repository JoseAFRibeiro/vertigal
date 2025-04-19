#version 450 core

out vec4 FragColor;

in vec3 FaceNormal;
in vec3 FragPos;

uniform vec3 lightPos;
uniform vec3 objectColor;
uniform vec3 lightColor;

void main()
{
    float ambientLightStrength = 0.1f;
    vec3 norm = normalize(FaceNormal);
    vec3 lightDir = normalize(FragPos - lightPos);
    float diff = max(dot(norm, lightDir), 0.0f);
    vec3 diffuse = diff * lightColor;
    vec3 res = (ambientLightStrength + diffuse) * objectColor;
    FragColor = vec4(res , 1.0f);
}