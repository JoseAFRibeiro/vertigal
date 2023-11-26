#include <stdint.h>
#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include "vertigal/glfuncs.h"
#include "vertigal/glstrcuts.h"
#include "vertigal/models.h"

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
    -0.5f, -0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
     0.0f,  0.5f, 0.0f
}; 

void renderLoop(GLFWwindow* win)
{
    VG_3D_ENTITY* cube = {0};
    uint32_t VBO, VAO, EBO;

    cube = loadModelFromObj("./res/cube.obj");
    glUseProgram(shaderProgram);
    
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    //FIXME: memory access violation ao mandar vertices para o GPU    
    glBufferData(GL_ARRAY_BUFFER, sizeof(VG_3D_VERTEX) * cube->attribs.numVertices, cube->vertexArray, GL_STATIC_DRAW);

    glGenVertexArrays(3, &VAO);
    glBindVertexArray(VAO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)3);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)5);
    glEnableVertexAttribArray(2);    
    

    //TODO: Deal with models returning NULL pointers
    
    while(!glfwWindowShouldClose(win))
    {   
        glfwPollEvents();
        glClearColor(0.70f, 0.83f, 0.69f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glfwSwapBuffers(win);
    }
}