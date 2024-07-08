#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include "cglm/vec3.h"
#include "stb_image.h"
#define NK_INCLUDE_FIXED_TYPES
#define NK_INCLUDE_STANDARD_IO
#define NK_INCLUDE_STANDARD_VARARGS
#define NK_INCLUDE_DEFAULT_ALLOCATOR
#define NK_INCLUDE_VERTEX_BUFFER_OUTPUT
#define NK_INCLUDE_FONT_BAKING
#define NK_INCLUDE_DEFAULT_FONT
#include "nuklear.h"
#include "nuklear_glfw_gl4.h"

static struct nk_context *ctx;
static struct nk_image img;
static int width, height;

int8_t loadGUIIcon(const char *file, struct nk_image *img_strc)
{
    int32_t x,y,numChannels;
    int32_t tex_h;
    uint8_t *data = NULL;
        
    data = stbi_load(file, &x, &y, &numChannels, 0);

    if(data == NULL) return -1;

    tex_h = nk_glfw3_create_texture(data, x, y);
    *img_strc = nk_image_id((int) tex_h);
    stbi_image_free(data);
    
    return 0;
}

uint8_t guiInit(GLFWwindow *win)
{   
    struct nk_font_atlas *fAtlas;
    struct nk_font *font;

    ctx = nk_glfw3_init(win, NK_GLFW3_INSTALL_CALLBACKS, 512 * 1024, 128 * 1024);

    nk_glfw3_font_stash_begin(&fAtlas);
    font = nk_font_atlas_add_from_file(fAtlas, "./res/DroidSans.ttf", 14, 0);
    nk_glfw3_font_stash_end();
    nk_style_set_font(ctx, &font->handle);

    loadGUIIcon("./res/images.png", &img);
    return 0;
}

void guiRender(GLFWwindow *win)
{   
    
    
    glfwGetWindowSize(win, &width, &height);
    glViewport(0, 0, width, height);
    nk_glfw3_render(NK_ANTI_ALIASING_ON);
}
