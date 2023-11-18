#include <stdint.h>
#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include "vertigal/glfuncs.h"
#include "vertigal/glstrcuts.h"

uint8_t rendererSetup(void)
{
    GLint shaderProgram;
    VG_shader_packet packet = {0};

    packet.vertex = compileShader("./res/vertex.glsl", GL_VERTEX_SHADER);
    packet.fragment = compileShader("./res/fragment.glsl", GL_FRAGMENT_SHADER);
    
    shaderProgram = compileShaderProgram(packet);
    glUseProgram(shaderProgram);
    return 0;
}

void renderLoop(GLFWwindow* win)
{

    loadModelFromObj("./res/cube.obj");

    while(!glfwWindowShouldClose(win))
    {   
        glfwPollEvents();
        glClearColor(0.70f, 0.83f, 0.69f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glfwSwapBuffers(win);
    }
}