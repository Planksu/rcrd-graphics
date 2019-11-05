#include <Shader.h>
#include <fstream>
#include <string>
#include <assert.h>

Shader::Shader()
{

}

std::string Shader::LoadShaderFromFile(const char* path)
{
	std::string shader;
	std::ifstream file(path, std::ios::in);

	if (!file.is_open())
	{
		RCRD_DEBUG("Could not open shader file!");
		return "ERROR";
	}

	std::string line = "";
	while (!file.eof())
	{
		std::getline(file, line);
		shader.append(line + "\n");
	}

	file.close();
	return shader;
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

void Shader::CreateShaderObject(std::string vertData, std::string fragData)
{
	GLuint vertexShader;
	GLuint fragmentShader;
	GLint linked;

	const char* vert = const_cast<char*>(vertData.c_str());
	const char* frag = const_cast<char*>(fragData.c_str());

	vertexShader = CompileShader(GL_VERTEX_SHADER, vert);
	fragmentShader = CompileShader(GL_FRAGMENT_SHADER, frag);

	program = glCreateProgram();

	assert(program != 0);

	glAttachShader(program, vertexShader);
	glAttachShader(program, fragmentShader);
	glBindAttribLocation(program, 0, "position");
	glLinkProgram(program);
	glGetProgramiv(program, GL_LINK_STATUS, &linked);

	if (!linked)
	{
		GLint infoLen = 0;

		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLen);

		if (infoLen > 1)
		{
			char* infoLog = (char*)malloc(sizeof(char) * infoLen);

			glGetProgramInfoLog(program, infoLen, NULL, infoLog);
			RCRD_DEBUG("Error linking program: " << infoLog);

			free(infoLog);
		}

		glDeleteProgram(program);
		return;
	}


	return;
}