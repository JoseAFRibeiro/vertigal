#include <stdio.h>
#include "vertigal/glfuncs.h"
int main()
{
    GLFWwindow * win;

    win = glInit();
    
    while(!glfwWindowShouldClose(win))
    {
        glfwPollEvents();
    } 

    return 0;
}