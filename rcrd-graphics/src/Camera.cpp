#include <Camera.h>

Camera::Camera(glm::vec3 p, glm::vec3 d, glm::vec3 tar, float f)
{
	pos = p;
	dir = d;
	target = tar;
	fov = f;
}