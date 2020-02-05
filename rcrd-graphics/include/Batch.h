#ifndef RCRD_BATCH_H
#define RCRD_BATCH_H

// GLEW
#include <glew/include/GL/glew.h>
#include <glm/glm.hpp>

#include <Vertex.h>
#include <Model.h>
#include <vector>
#include <core.h>


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