#ifndef RCRD_INPUTSYSTEM_H
#define RCRD_INPUTSYSTEM_H

// GLFW
#include <GLFW/glfw3.h>

// GLM
#include <glm/glm.hpp>

#include <core.h>
#include <Camera.h>

class InputSystem
{
public:
	InputSystem(float centerX, float centerY);
	~InputSystem();

	void Update(GLFWwindow* window, Camera* camera);
	void HandleMovement(GLFWwindow* window, Camera* camera);
	void HandleRotation(GLFWwindow* window, Camera* camera);
	void CalculateDelta();

private:

public:

private:

	// Frame variables
	float dt = 0.0f;
	float last = 0.0f;

	// Input variables
	float lastX;
	float lastY;
	float yaw;
	float pitch;
	bool firstMouse = true;
	const float cameraSpeed = 5.f;
	const float sens = 0.05f;
};

#endif // RCRD_INPUTSYSTEM_H