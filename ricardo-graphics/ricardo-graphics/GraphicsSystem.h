#ifndef _GRAPHICSSYSTEM_HEADER_
#define _GRAPHICSSYSTEM_HEADER_

// GLEW
#include <GL/glew.h>

// GLFW
//#include <GLFW/glfw3.h>
//#include <glfw3.h>
#include <include/glfw/glfw3.h>

// GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <vector>
#include "Object.h"

#define yeet throw

class GraphicsSystem
{
public:
	GraphicsSystem(int width, int height, const char* title);
	~GraphicsSystem();

	void InitGLFW(const char* title);
	void InitGL();
	void LoadOBJ(const char* path);
	void Draw();
	void GenerateGLBuffers();
	std::string LoadShaderFromFile(const std::string &filename);
	void CreateShaderObject(char* vShaderSrc, char* fShadersrc, GLuint* object);
	void InitShaders();


private:
	GLuint VAO, VBO, EBO;
	GLFWwindow* window;
	GLuint program;

	int width, height;

	std::vector<Object> objects;

};

#endif