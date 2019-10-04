#ifndef RCRD_VERTEX_H
#define RCRD_VERTEX_H

#include <glm/glm.hpp>

struct Vertex
{
	glm::vec3 vert;
    glm::vec3 norm;
    glm::vec2 texCoord;
};

#endif