#include <Camera.h>

Camera::Camera(glm::vec3 p, glm::vec3 r, float f)
{
	pos = p;
	rot = r;
	fov = f;
}