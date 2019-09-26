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
#include <core.h>

class GraphicsSystem
{
public:
	GraphicsSystem(int width, int height, const char* title);
	~GraphicsSystem();

	void InitGLFW(const char* title);
	void InitGL();
	void Draw();
	std::string LoadShaderFromFile(const std::string &filename);
	void CreateShaderObject(char* vShaderSrc, char* fShadersrc, GLuint* object);
	void InitShaders();
	void InitLight();
	Batch* CreateBatch();


private:
	GLFWwindow* window;
	GLuint program;
	std::vector<Batch*> batches;

	Light* light;

	int width, height;

};

#endif