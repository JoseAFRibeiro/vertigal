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
#include "vertigal/arena.h"

GLint shaderProgram;
GLint shaderProgram2;


uint8_t rendererSetup(void)
{
    VG_shader_packet packet = {0};

    packet.vertex = compileShader("./res/vertex.glsl", GL_VERTEX_SHADER);
    packet.fragment = compileShader("./res/fragment.glsl", GL_FRAGMENT_SHADER);
    packet.numShaders = 2;

    shaderProgram = compileShaderProgram(packet);

    packet.vertex = compileShader("./res/vertex.glsl", GL_VERTEX_SHADER);
    packet.fragment = compileShader("./res/lighting.glsl", GL_FRAGMENT_SHADER);
    packet.geometry = compileShader("./res/geometry.glsl", GL_GEOMETRY_SHADER);
    packet.numShaders = 3;
    
    shaderProgram2 = compileShaderProgram(packet);

    return 0;
}

float vertices[] = {
    0.0f,  0.0f,  0.0f,
    0.0f,  0.0f,  1.0f,
    0.0f,  1.0f,  0.0f,
    0.0f,  1.0f,  1.0f,
    1.0f,  0.0f,  0.0f,
    1.0f,  0.0f,  1.0f,
    1.0f,  1.0f,  0.0f,
    1.0f,  1.0f,  1.0f
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
    VG_3D_ENTITY* model1 = {0};
    VG_3D_ENTITY* model2 = {0};
    uint32_t VBO, VAO, VAO2, EBO, VBO2, EBO2;
    //guiInit(win);
    int idx = 0;
    model1 = loadModelFromObj("./res/cube.obj");
    model2 = loadModelFromObj("./res/cow.obj");


    VERTIGAL_MODEL_ARENA* arena = getArenaptr();
    
    VERTIGAL_ARENA_MODEL_IDENTIFIER id = arena->modelHandlePool[idx];
    VERTIGAL_ARENA_MODEL_IDENTIFIER id2 = arena->modelHandlePool[idx+1];

    VERTIGAL_ARENA_MODEL_IDENTIFIER id_arr[2] = {id, id2};
    
    //if(cube == NULL) return;
    glUseProgram(shaderProgram);

    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, (arena->sizeIndexes - arena->freeIndexes) * sizeof(uint32_t), arena->indexes, GL_STATIC_DRAW);
    //glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vec3) * (arena->sizeVertices - arena->freeVertices), arena->vertices, GL_STATIC_DRAW);

    glGenVertexArrays(1, &VAO);
    glGenVertexArrays(1, &VAO2);

    glBindVertexArray(VAO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(VAO2);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*) (id.verticesSLen * sizeof(vec3)));
    glEnableVertexAttribArray(0);

    /*Temporary triangle transform*/
    mat4 cowTransform = GLM_MAT4_IDENTITY_INIT;
    mat4 cubeTransform = GLM_MAT4_IDENTITY_INIT;
    GLint objectTransformLoc = glGetUniformLocation(shaderProgram, "model");
    /*Temporary triangle transform*/
    
    /*Temporary camera transform*/
    VG_PLAYER_CAMERA cam = cameraSetup();
    GLint cameraTransformLoc = glGetUniformLocation(shaderProgram, "view");
    /*Temporary camera transform*/

    /*Temporary projection transform*/
    mat4 projection = GLM_MAT4_IDENTITY_INIT;
    glm_perspective(glm_rad(45), 16/9, 0.1f, 100.0f, projection);
    GLint projectionTransformLoc = glGetUniformLocation(shaderProgram, "projection");
    /*Temporary projection transform*/

    /*temporary light and cow color*/
    
    vec3 light = {1.0f, 1.0f, 1.0f};
    vec3 cubeColor = {1.0f, 1.0f, 1.0f};
    vec3 cowColor = {1.0f, 0.5f, 0.31f};

    GLint lightUniformLocation = glGetUniformLocation(shaderProgram, "lightColor");
    GLint objectColorUniformLocation = glGetUniformLocation(shaderProgram2, "objectColor");
    /*temporary light and cow color*/

    glfwSwapInterval(1);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);

    vec3 cubeTranslate = {10.0f, 0.0f, 0.0f};
    glm_translate(cubeTransform, cubeTranslate);

    glDisable(GL_CULL_FACE);
    while(!glfwWindowShouldClose(win))
    {   
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glfwPollEvents();

        if(glfwGetKey(win, GLFW_KEY_ENTER ) == GLFW_PRESS)
        {
            idx = !idx;
            id = arena->modelHandlePool[idx];
            printf("IDX: %d\n", idx);
        }

        glUseProgram(shaderProgram);

        objectTransformLoc = glGetUniformLocation(shaderProgram, "model");
        cameraTransformLoc = glGetUniformLocation(shaderProgram, "view");
        projectionTransformLoc = glGetUniformLocation(shaderProgram, "projection");
        lightUniformLocation = glGetUniformLocation(shaderProgram, "lightColor");
        objectColorUniformLocation = glGetUniformLocation(shaderProgram, "objectColor");

        glEnable(GL_DEPTH_TEST);
        glClearColor(0.50f, 0.70f, 0.40f, 1.0f);
        
        moveCamera(&cam, win);
        //setPosition(cam.cameraPosition);
        glUniformMatrix4fv(projectionTransformLoc, 1, GL_FALSE, (float *) projection);
        glUniformMatrix4fv(cameraTransformLoc, 1, GL_FALSE, (float *) cam.lookat);
        glUniform3fv(lightUniformLocation, 1, (float *) light);

        glBindVertexArray(VAO);
        glEnableVertexAttribArray(0);        
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        
        glUniformMatrix4fv(objectTransformLoc, 1, GL_FALSE, (float *) cubeTransform);
        glUniform3fv(objectColorUniformLocation, 1 , (float *) cubeColor);
        glDrawElements(GL_TRIANGLES, id_arr[0].indexLen, GL_UNSIGNED_INT, (void*) (id_arr[0].indexStart * sizeof(int32_t)));
        glDisableVertexAttribArray(0);

        glm_spinned(cowTransform, glm_rad(0.3f), cam.__cameraUp);
        
        glUseProgram(shaderProgram2);

        objectTransformLoc = glGetUniformLocation(shaderProgram2, "model");
        cameraTransformLoc = glGetUniformLocation(shaderProgram2, "view");
        projectionTransformLoc = glGetUniformLocation(shaderProgram2, "projection");
        lightUniformLocation = glGetUniformLocation(shaderProgram2, "lightColor");
        objectColorUniformLocation = glGetUniformLocation(shaderProgram2, "objectColor");
        GLint lightPosUniformLocation = glGetUniformLocation(shaderProgram2, "lightPos");

        glBindVertexArray(VAO2);
        glEnableVertexAttribArray(0);        
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

        glUniformMatrix4fv(projectionTransformLoc, 1, GL_FALSE, (float *) projection);
        glUniformMatrix4fv(objectTransformLoc, 1, GL_FALSE, (float *) cowTransform);
        glUniformMatrix4fv(cameraTransformLoc, 1, GL_FALSE, (float *) cam.lookat);
        glUniform3fv(objectColorUniformLocation, 1, (float *) cowColor);
        glUniform3fv(lightUniformLocation, 1, (float *) light);
        glUniform3fv(lightPosUniformLocation, 1, (float *) cubeTranslate);


        glDrawElements(GL_TRIANGLES, id_arr[1].indexLen, GL_UNSIGNED_INT, (void*) (id_arr[1].indexStart * sizeof(int32_t)));
        glDisableVertexAttribArray(0);

        //guiRender(win);

        glfwSwapBuffers(win);
    }
}