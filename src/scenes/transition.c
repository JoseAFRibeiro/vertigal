#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "vertigal/scene.h"
#include "vertigal/arena.h"
#include "vertigal/models.h"

static SceneTree* tree;
static SceneNode* currentNode;

void setTree(SceneTree* t)
{
    tree = t;
    return;
}

void setCurrentSceneToRoot()
{
    GLint VBO;
    GLint VAO;
    GLint EBO;

    VERTIGAL_MODEL_ARENA* arena = getArenaptr();
    
    currentNode = tree->root;

    glGetIntegerv(GL_ARRAY_BUFFER_BINDING, &VAO);
    glGetIntegerv(GL_ELEMENT_ARRAY_BUFFER_BINDING, &EBO);
    glGetIntegerv(GL_ARRAY_BUFFER_BINDING, &VBO);
    
    glInvalidateBufferData(VBO);
    glInvalidateBufferData(EBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vec3) * tree->root->verticesLen, &arena->vertices[tree->root->verticesStart], GL_STATIC_DRAW);
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int32_t) * (tree->root->indicesLen * 3), &arena->indexes[tree->root->indicesStart], GL_STATIC_DRAW);

}

void transitionScene(SceneNode* newNode)
{
    GLint VBO;
    GLint VAO;
    GLint EBO;

    size_t sceneVertexSize = 0;
    size_t sceneVertexStart = 0;
    size_t sceneIndexSize = 0;
    size_t sceneIndexStart = 0;

    VERTIGAL_MODEL_ARENA* arena = getArenaptr();

    //store already bound buffers
    
    glGetIntegerv(GL_ARRAY_BUFFER_BINDING, &VAO);
    glGetIntegerv(GL_ELEMENT_ARRAY_BUFFER_BINDING, &EBO);
    glGetIntegerv(GL_ARRAY_BUFFER_BINDING, &VBO);
    
    glInvalidateBufferData(VBO);
    //glInvalidateBufferData(VAO);
    glInvalidateBufferData(EBO);
    
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vec3) * newNode->verticesLen, &arena->vertices[newNode->verticesStart], GL_STATIC_DRAW);
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int32_t) * (newNode->indicesLen * 3), &arena->indexes[newNode->indicesStart], GL_STATIC_DRAW);

    currentNode = newNode;
}
