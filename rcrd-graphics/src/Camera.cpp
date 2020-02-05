#include <Camera.h>

Camera::Camera(glm::vec3 p, glm::vec3 d, glm::vec3 tar, float f)
{
	pos = p;
	dir = d;
	target = tar;
	fov = f;
}

void Camera::MoveVertical(float multiplier, float cameraSpeed)
{
	pos += (cameraSpeed * front) * multiplier;
}

void Camera::MoveHorizontal(float multiplier, float cameraSpeed)
{
	pos += (glm::normalize(glm::cross(front, up)) * cameraSpeed) * multiplier;
}