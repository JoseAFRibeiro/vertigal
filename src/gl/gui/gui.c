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
static char positionX[200];
static char positionY[200];
static char positionZ[200];

void setPosition(vec3 vec)
{
    snprintf(positionX, 200, "X: %f", vec[0]);
    snprintf(positionY, 200, "Y: %f", vec[1]);
    snprintf(positionZ, 200, "Z: %f", vec[2]);
}

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
    
    nk_glfw3_new_frame();
    if (nk_begin(ctx, "Keep dreaming!", nk_rect(50, 50, 500, 500), NK_WINDOW_BORDER | NK_WINDOW_MOVABLE | NK_WINDOW_SCALABLE | NK_WINDOW_MINIMIZABLE | NK_WINDOW_TITLE))
    {
        //nk_layout_row_static(ctx, 50, 80, 1);
        /*if(nk_button_image(ctx, img))
        {
            fprintf(stdout, "Dream On!\n");
        }*/

        if(nk_tree_push(ctx, NK_TREE_NODE, "Camera", NK_MINIMIZED))
        {
            nk_layout_row_dynamic(ctx, 30, 3);
            nk_label(ctx, positionX, NK_TEXT_ALIGN_CENTERED);
            nk_label(ctx, positionY, NK_TEXT_ALIGN_CENTERED);
            nk_label(ctx, positionZ, NK_TEXT_ALIGN_CENTERED);
            nk_tree_pop(ctx);
        }

    }
    nk_end(ctx);
    
    int width = 0, height = 0;
    
    glfwGetWindowSize(win, &width, &height);
    glViewport(0, 0, width, height);
    /* IMPORTANT: `nk_glfw_render` modifies some global OpenGL state
     * with blending, scissor, face culling, depth test and viewport and
     * defaults everything back into a default state.
     * Make sure to either a.) save and restore or b.) reset your own state after
     * rendering the UI. */
    nk_glfw3_render(NK_ANTI_ALIASING_ON);
}