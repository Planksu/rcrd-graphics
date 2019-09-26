#ifndef RCRD_LIGHT_H
#define RCRD_LIGHT_H

#include <glm/glm.hpp>

class Light
{
public:

	Light(glm::vec3 pos, glm::vec3 col, glm::vec3 am_col, float shin);

	glm::vec3 position;
	glm::vec3 color;
	glm::vec3 ambient_color;
	float shininess;

};

#endif