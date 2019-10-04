#include <Shader.h>
#include <fstream>
#include <string>
#include <assert.h>

Shader::Shader()
{

}

void Shader::LoadShaderFromFile(const char* path)
{
	std::string shader;
	std::ifstream file(path, std::ios::in);

	if (!file.is_open())
	{
		RCRD_DEBUG("Could not open shader file!");
		return;
	}

	std::string line = "";
	while (!file.eof())
	{
		std::getline(file, line);
		shader.append(line + "\n");
	}

	file.close();
	
}

GLuint Shader::CompileShader(GLenum type, const char* src)
{
	GLuint shader;
	GLint compiled;
	shader = glCreateShader(type);
	assert(shader != 0);

	glShaderSource(shader, 1, &src, NULL);
	glCompileShader(shader);
	glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);

	if (!compiled)
	{
		GLint infoLen = 0;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLen);
		if (infoLen > 1)
		{
			char* infoLog = (char*)malloc(sizeof(char) * infoLen);
			glGetShaderInfoLog(shader, infoLen, NULL, infoLog);
			RCRD_DEBUG("Error compiling shader: " << infoLog);
			free(infoLog);
		}
		glDeleteShader(shader);
		return 0;
	}
	return shader;
}

void Shader::CreateShaderObject()
{
	GLuint vertexShader;
	GLuint fragmentShader;
	GLint linked;

	vertexShader = CompileShader(GL_VERTEX_SHADER, vShaderSrc);
	fragmentShader = CompileShader(GL_FRAGMENT_SHADER, fShaderSrc);

	*object = glCreateProgram();

	assert(*object != 0);

	glAttachShader(*object, vertexShader);
	glAttachShader(*object, fragmentShader);
	glBindAttribLocation(*object, 0, "position");
	glLinkProgram(*object);
	glGetProgramiv(*object, GL_LINK_STATUS, &linked);

	if (!linked)
	{
		GLint infoLen = 0;

		glGetProgramiv(*object, GL_INFO_LOG_LENGTH, &infoLen);

		if (infoLen > 1)
		{
			char* infoLog = (char*)malloc(sizeof(char) * infoLen);

			glGetProgramInfoLog(*object, infoLen, NULL, infoLog);
			RCRD_DEBUG("Error linking program: " << infoLog);

			free(infoLog);
		}

		glDeleteProgram(*object);
		return;
	}


	return;
}