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
#include <InputSystem.h>

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
	void InitShaders();
	void InitLight();
	void InitCamera();
	void InitInputSystem();
	void Update();
	void MoveLights();
	void SetupShadowMapVars();
	void RenderScene(Shader* shader, RENDER_MODE mode);
	void FillSceneMatrices(glm::mat4 &model, glm::mat4& view, glm::mat4& projection);
	void CreateShadowMap();
	void ClearBuffer();
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
	InputSystem* inputSystem;

	// Render distances
	float near = 1.0f;
	float far = 50.f;
};

#endif