#include <stdio.h>
#include "vertigal/glfuncs.h"
int main()
{
    GLFWwindow * win;

    win = glInit();
    
    uint8_t code = rendererSetup();
    renderLoop(win);

    return 0;
}