#include <InputSystem.h>

InputSystem::InputSystem(float centerX, float centerY)
{
	float lastX = centerX;
	float lastY = centerY;
}

InputSystem::~InputSystem()
{
}

void InputSystem::CalculateDelta()
{
	float currentFrame = glfwGetTime();
	dt = currentFrame - last;
	last = currentFrame;
}

void InputSystem::Update(GLFWwindow* window, Camera* camera)
{
	glfwPollEvents();
	CalculateDelta();
	HandleMovement(window, camera);
	HandleRotation(window, camera);
}

void InputSystem::HandleMovement(GLFWwindow* window, Camera* camera)
{
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera->MoveVertical(1, cameraSpeed * dt);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera->MoveVertical(-1, cameraSpeed * dt);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera->MoveHorizontal(-1, cameraSpeed * dt);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera->MoveHorizontal(1, cameraSpeed * dt);
}

void InputSystem::HandleRotation(GLFWwindow* window, Camera* camera)
{
	double x, y;
	glfwGetCursorPos(window, &x, &y);

	if (firstMouse)
	{
		lastX = x;
		lastY = y;
		firstMouse = false;
	}

	float xOffset = x - lastX;
	float yOffset = lastY - y;
	lastX = x;
	lastY = y;

	xOffset *= sens;
	yOffset *= sens;
	yaw += xOffset;
	pitch += yOffset;

	// Limit to prevent flip
	if (pitch > 89.0f)
		pitch = 89.0f;
	if (pitch < -89.0f)
		pitch = -89.0f;

	glm::vec3 direction;
	direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	direction.y = sin(glm::radians(pitch));
	direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	camera->front = glm::normalize(direction);
}