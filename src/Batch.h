#ifndef _BATCH_HEADER
#define _BATCH_HEADER

// GLEW
#include <GL/glew.h>
#include <glm/glm/glm.hpp>

#include "Vertex.h"
#include "Model.h"
#include <vector>

class Batch
{
public:
    Batch();
    void GenerateBuffers();
    void LoadObject(const char* obj_path, const char* mtl_path);

public:
    std::vector<Model> models;
    GLuint VAO, vertexes, normals;


};

#endif