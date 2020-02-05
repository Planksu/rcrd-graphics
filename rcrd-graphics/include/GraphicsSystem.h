#ifndef RCRD_GRAPHICSSYSTEM_H
#define RCRD_GRAPHICSSYSTEM_H

#undef GLFW_DLL

// GLEW
#include <glew/include/GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

// GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <vector>

#include <Object.h>
#include <Batch.h>
#include <Light.h>
#include <Camera.h>
#include <core.h>
#include <Shader.h>

enum RENDER_MODE
{
	DEPTH = 0,
	FRAGMENT = 1,
};


class GraphicsSystem
{
public:
	GraphicsSystem(int width, int height, const char* title);
	~GraphicsSystem();

	void InitGLFW(const char* title);
	void InitGL();
	void Draw();
	void SetupShadowMapVars();
	void RenderScene(Shader* shader, RENDER_MODE mode);
	void CreateShadowMap();
	void InitShaders();
	void InitLight();
	void InitCamera();
	void HandleInput();
	void HandleMovement();
	void HandleMouse();
	Batch* CreateBatch();


private:

	// Window
	GLFWwindow* window;
	int width, height;
	int SHADOW_WIDTH = 1024, SHADOW_HEIGHT = 1024;

	// Containers
	std::vector<Batch*> batches;
	std::vector<GLchar*> shadowTransformNames;

	// Frame buffer objects etc.
	GLuint depthMapFBO;
	GLuint depthCubemap;

	// Other objects
	Light* light;
	Camera* camera;
	Shader* mainShader;
	Shader* depthShader;

	// Render distances
	float near = 1.0f;
	float far = 25.f;

	// Mouse variables
	float lastX = 640;
	float lastY = 360;
	float yaw = -90.f;
	float pitch = 0.0f;
	bool firstMouse = true;

	// Frame variables
	float dt = 0.0f;
	float last = 0.0f;
};

#endif