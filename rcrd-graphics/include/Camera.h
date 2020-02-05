#ifndef RCRD_CAMERA_H
#define RCRD_CAMERA_H

#include <core.h>
#include <glm/glm.hpp>


class Camera
{
public:
	glm::vec3 pos;
	glm::vec3 dir;
	glm::vec3 target;
	glm::vec3 front;

	glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
	float fov;

	void MoveVertical(float multiplier, float cameraSpeed);
	void MoveHorizontal(float multiplier, float cameraSpeed);

	Camera(glm::vec3 p, glm::vec3 d, glm::vec3 tar, float f);
};


#endif