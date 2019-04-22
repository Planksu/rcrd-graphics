#ifndef _GRAPHICSSYSTEM_HEADER_
#define _GRAPHICSSYSTEM_HEADER_

#undef GLFW_DLL

// GLEW
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

// GLM
#include <glm/glm/glm.hpp>
#include <glm/glm/gtc/matrix_transform.hpp>
#include <glm/glm/gtc/type_ptr.hpp>

#include <vector>
#include "Object.h"
#include "Batch.h"

#define yeet throw

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
	Batch* CreateBatch();


private:
	GLFWwindow* window;
	GLuint program;
	std::vector<Batch> batches;

	int width, height;

};

#endif