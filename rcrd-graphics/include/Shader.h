#ifndef RCRD_SHADER_H
#define RCRD_SHADER_H

#include <glew/include/GL/glew.h>
#include <core.h>

class Shader
{
public:
	Shader();

	std::string LoadShaderFromFile(const char* path);
	GLuint CompileShader(GLenum type, const char* src);
	void CreateShaderObject(std::string vertData, std::string fragData);


private:
	char* fragShader;
	char* vertShader;

public:

	GLuint program;
};

#endif