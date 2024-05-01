#include <stdint.h>
#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include "vertigal/glfuncs.h"
#include "vertigal/glstrcuts.h"
#include "vertigal/models.h"
#include "vertigal/camera.h"
#include "vertigal/iofuncs.h"
#include "cglm/mat4.h"
#include "cglm/cam.h"
#include "cglm/affine.h"

GLint shaderProgram;

uint8_t rendererSetup(void)
{
    VG_shader_packet packet = {0};

    packet.vertex = compileShader("./res/vertex.glsl", GL_VERTEX_SHADER);
    packet.fragment = compileShader("./res/fragment.glsl", GL_FRAGMENT_SHADER);
    
    shaderProgram = compileShaderProgram(packet);
    return 0;
}

float vertices[] = {
    0.0f,  0.0f , 0.0f,
    0.0f,  0.0f , 0.0f,
    0.0f,  0.0f , 1.0f,
    0.0f,  1.0f , 0.0f,
    0.0f,  1.0f , 1.0f,
    1.0f,  0.0f , 0.0f,
    1.0f,  0.0f , 1.0f,
    1.0f,  1.0f , 0.0f,
    1.0f,  1.0f , 1.0f
}; 

unsigned int indices[] = {
    1, 7,  5,
    1, 3,  7, 
    1, 4,  3, 
    1, 2,  4, 
    3, 8,  7, 
    3, 4,  8, 
    5, 7,  8, 
    5, 8,  6, 
    1, 5,  6, 
    1, 6,  2, 
    2, 6,  8, 
    2, 8,  4 
};

void renderLoop(GLFWwindow* win)
{
    VG_3D_ENTITY* cube = {0};
    uint32_t VBO, VAO, EBO;

    cube = loadModelFromObj("./res/cube.obj");
    glUseProgram(shaderProgram);
    for(int i = 0; i< sizeof(indices)/sizeof(int); i++)
    {
        indices[i] = indices[i] - 1;
    }
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, cube->attribs.numFaces * sizeof(uint32_t), cube->faceIndices, GL_STATIC_DRAW);
    
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    //vg_printArrayVertex((float*)cube->vertexArray, cube->attribs.numVertices);
    //FIXME: memory access violation ao mandar vertices para o GPU    
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vec3) * cube->attribs.numFaces, cube->vertexArray, GL_STATIC_DRAW);

    glGenVertexArrays(3, &VAO);
    glBindVertexArray(VAO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)3);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)5);
    glEnableVertexAttribArray(2);    

    /*Temporary triangle transform*/
    mat4 triangleTransform = GLM_MAT4_IDENTITY_INIT;
    uint16_t triangleTransformLoc = glGetUniformLocation(shaderProgram, "model");
    /*Temporary triangle transform*/
    
    /*Temporary camera transform*/
    VG_PLAYER_CAMERA cam = cameraSetup();
    uint16_t cameraTransformLoc = glGetUniformLocation(shaderProgram, "view");
    /*Temporary camera transform*/

    /*Temporary projection transform*/
    mat4 projection = GLM_MAT4_IDENTITY_INIT;
    glm_perspective(glm_rad(45), 16/9, 0.1f, 100.0f, projection);
    uint16_t projectionTransformLoc = glGetUniformLocation(shaderProgram, "projection");
    /*Temporary projection transform*/

    glfwSwapInterval(1);
    glBindVertexArray(VAO);
    while(!glfwWindowShouldClose(win))
    {   
        glfwPollEvents();
        glEnable(GL_DEPTH_TEST);
        glClearColor(0.70f, 0.83f, 0.69f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        moveCamera(&cam, win);

        glm_spinned(triangleTransform, glm_rad(3), cam.__cameraUp);
        glUniformMatrix4fv(triangleTransformLoc, 1, GL_FALSE, (float *) triangleTransform);
        glUniformMatrix4fv(projectionTransformLoc, 1, GL_FALSE, (float *) projection);
        glUniformMatrix4fv(cameraTransformLoc, 1, GL_FALSE, (float *) cam.lookat);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
        //glDrawArrays(GL_TRIANGLES, 0, 3);
        glfwSwapBuffers(win);
    }
}