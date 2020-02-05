#ifndef RCRD_SHADER_H
#define RCRD_SHADER_H

#include <glew/include/GL/glew.h>
#include <glm/glm.hpp>
#include <core.h>
#include <Material.h>

class Shader
{
public:
	Shader();

	std::string LoadShaderFromFile(const char* path);
	GLuint CompileShader(GLenum type, const char* src);
	void CreateShaderObject(std::string vertData, std::string fragData);
	void CreateShaderObject(std::string vertData, std::string fragData, std::string geomData);

	void SetVec3Uniform(GLchar* uniformName, glm::vec3 data);
	void SetVec3Uniform(GLchar* uniformName, Color color);
	void SetMat4Uniform(GLchar* uniformName, glm::mat4 data);
	void SetFloatUniform(GLchar* uniformName, float data);
	void SetIntUniform(GLchar* uniformName, int data);


private:
	char* fragShader;
	char* vertShader;

public:

	GLuint program;
};

#endif