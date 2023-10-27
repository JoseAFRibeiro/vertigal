#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include "vertigal/callback.h"

GLFWwindow* glInit(void)
{
    GLFWwindow* win;

    #ifdef DEBUG
    glfwSetErrorCallback(errorCallback);
    #endif

    if(!glfwInit())
    {
        glfwTerminate();
        return NULL;
    } 

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    win = glfwCreateWindow(1920, 1080, "Vertigal", NULL, NULL);

    if(win == NULL)
    {
        glfwTerminate();
        return NULL;
    } 

    glfwMakeContextCurrent(win);
    glfwSetFramebufferSizeCallback(win, frameBufferSizeCallback);
    glfwSetKeyCallback(win, keyPressedCallback);

    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        glfwTerminate();
        return NULL;
    }

    #ifdef DEBUG
    glEnable(GL_DEBUG_OUTPUT);
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
    glDebugMessageCallback(DebugCallback, NULL);
    #endif

    glViewport(0, 0, 1920, 1080);
    return win;
}




