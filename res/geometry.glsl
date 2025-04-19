#version 450 core

layout (triangles) in;
layout (triangle_strip, max_vertices = 3) out;

in mat4 modelMat[];
out vec3 FaceNormal;

void main(){

    vec3 normalU;
    vec3 normalV;

    vec3 vert1 = gl_in[0].gl_Position.xyz;
    vec3 vert2 = gl_in[1].gl_Position.xyz;
    vec3 vert3 = gl_in[2].gl_Position.xyz; 

    normalU = vert2 - vert1;
    normalV = vert3 - vert1;

    float FaceNormalX = (normalU.y * normalV.z) - (normalU.z * normalV.y);  
    float FaceNormalY = (normalU.z * normalV.x) - (normalU.x * normalV.z);
    float FaceNormalZ = (normalU.x * normalV.y) - (normalU.y * normalV.z);

    FaceNormal = vec3(FaceNormalX, FaceNormalY, FaceNormalZ);
    //FaceNormal = mat3(transpose(inverse(modelMat))) * FaceNormal;
    for(int i = 0;i < gl_in.length();i++)
    {
        gl_Position = gl_in[i].gl_Position;
        EmitVertex();
    }

    EndPrimitive();
}
