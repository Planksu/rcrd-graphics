#include <iostream>
#include <GLFW/glfw3.h>
#include <glm.hpp>
#include <exception>
#include "Loader.h"

#define yeet throw

void error_callback(int error, const char* description);

void error_callback(int error, const char* description)
{
	fprintf(stderr, "Error: %s\n", description);
}

int main(int argc, char* argv[])
{
	if (!glfwInit())
	{
		yeet new std::exception();
	}

	glfwSetErrorCallback(error_callback);

	GLFWwindow* window = glfwCreateWindow(640, 480, "My Title", NULL, NULL);

	if (!window)
	{
		yeet new std::exception();
	}

	std::cout << "This code is being executed" << std::endl;

	Loader loader;
	loader.LoadOBJ("C://Users//anttonjok//Documents//ricardo-graphics//Cube.obj");

	glfwTerminate();
}