#ifndef _VERTEX_HEADER
#define _VERTEX_HEADER

#include <glm/glm/glm.hpp>

struct Vertex
{
	glm::vec3 vert;
    glm::vec3 norm;
    glm::vec2 texCoord;
};

#endif