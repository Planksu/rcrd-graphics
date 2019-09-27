#ifndef RCRD_CAMERA_H
#define RCRD_CAMERA_H

#include <core.h>
#include <glm/glm.hpp>


class Camera
{
public:
	glm::vec3 pos;
	glm::vec3 rot;
	float fov;

	Camera(glm::vec3 p, glm::vec3 r, float f);
};


#endif