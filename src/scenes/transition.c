#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "vertigal/scene.h"
#include "vertigal/arena.h"
#include "vertigal/models.h"

static SceneTree tree;
static SceneNode currentNone;

void setTree(SceneTree t)
{
    tree = t;
    return;
}

void transitionScene(/*GLFWwindow *win, SceneNode* newScene*/)
{
    GLint VBO;
    GLint VAO;
    GLint EBO;

    VG_3D_ENTITY* model1 = loadModelFromObj("./res/cube.obj");
    VG_3D_ENTITY* model2 = loadModelFromObj("./res/teapot.obj");

    VERTIGAL_MODEL_ARENA* arena = getArenaptr();
    VERTIGAL_ARENA_MODEL_IDENTIFIER cubeID = arena->modelHandlePool[2];
    //store already bound buffers

    glGetIntegerv(GL_ARRAY_BUFFER_BINDING, &VAO);
    glGetIntegerv(GL_ELEMENT_ARRAY_BUFFER_BINDING, &EBO);
    glGetIntegerv(GL_ARRAY_BUFFER_BINDING, &VBO);
    
    glInvalidateBufferData(VBO);
    glInvalidateBufferData(VAO);
    glInvalidateBufferData(EBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vec3) * (model1->attribs.numVertices + model2->attribs.numVertices), &arena->vertices[cubeID.verticesStart], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int32_t) * ((model1->attribs.numFaces * 3) + (model2->attribs.numFaces * 3)), &arena->indexes[cubeID.indexStart], GL_STATIC_DRAW);
}
