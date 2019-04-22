#ifndef _BATCH_HEADER
#define _BATCH_HEADER

// GLEW
#include <GL/glew.h>


#include "Object.h"
#include <vector>

class Batch
{
public:
    Batch();
    void GenerateBuffers();
    void LoadObject(const char* path);

public:
    std::vector<Object> objects;
    GLuint currentVAOIndex;
    GLuint VAO, VBO, EBO;


};

#endif