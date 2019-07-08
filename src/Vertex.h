#ifndef _VERTEX_HEADER
#define _VERTEX_HEADER

#include <glm/glm/glm.hpp>

class Vertex
{
public:

	Vertex();

	glm::vec3 vert;
    glm::vec2 texCoord;
    glm::vec3 norm;
};

#endif