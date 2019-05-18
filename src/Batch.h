#ifndef _BATCH_HEADER
#define _BATCH_HEADER

// GLEW
#include <GL/glew.h>
#include <glm/glm/glm.hpp>


#include "Model.h"
#include <vector>

class Batch
{
public:
    Batch();
    void GenerateBuffers();
    void LoadObject(const char* path);

public:
    std::vector<Model> models;
    GLuint VAO, VBO, EBO;


};

#endif