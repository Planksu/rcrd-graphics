#ifndef RCRD_SHADER_H
#define RCRD_SHADER_H

#include <glew/include/GL/glew.h>
#include <core.h>

class Shader
{
public:
	Shader();

	void LoadShaderFromFile(const char* path);
	GLuint CompileShader(GLenum type, const char* src);
	void CreateShaderObject();


private:
	const char* fragShader;
	const char* vertShader;

public:

	GLuint program;
};

#endif