#include "GraphicsSystem.h"

GraphicsSystem::GraphicsSystem(int w, int h, const char* title)
{
	width = w; height = h;
	InitGLFW(title);
	InitGL();
	InitShaders();
}

GLuint LoadShader(GLenum type, const char *shaderSrc)
{
	GLuint shader;
	GLint compiled;
	shader = glCreateShader(type);
	assert(shader != 0);

	glShaderSource(shader, 1, &shaderSrc, NULL);
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
			printf("Error compiling shader:\n%s\n", infoLog);
			free(infoLog);
		}
		glDeleteShader(shader);
		return 0;
	}
	return shader;
}


GraphicsSystem::~GraphicsSystem()
{
}

void error_callback(int error, const char* description)
{
	fprintf(stderr, "Error: %s\n", description);
}

#pragma region Shader methods

std::string GraphicsSystem::LoadShaderFromFile(const std::string& filename)
{
	// Load shaders from txt file
	std::string shader;

	std::ifstream file(filename, std::ios::in);

	if (!file.is_open())
	{
		printf("Could not open shader file!");
		return shader;
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

void GraphicsSystem::CreateShaderObject(char* vShaderSrc, char* fShaderSrc, GLuint* object)
{
	GLuint vertexShader;
	GLuint fragmentShader;
	GLint linked;

	vertexShader = LoadShader(GL_VERTEX_SHADER, vShaderSrc);
	fragmentShader = LoadShader(GL_FRAGMENT_SHADER, fShaderSrc);

	*object = glCreateProgram();

	assert(*object != 0);

	glAttachShader(*object, vertexShader);
	glAttachShader(*object, fragmentShader);
	glBindAttribLocation(*object, 0, "inVertexPosition");
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
			printf("Error linking program:\n%s\n", infoLog);

			free(infoLog);
		}

		glDeleteProgram(*object);
		return;
	}

	glClearColor(0.2f, 0.2f, 0.2f, 0.0f);
	return;
}

void GraphicsSystem::InitShaders()
{
	std::string vert = LoadShaderFromFile("vertShader.txt");
	std::string frag = LoadShaderFromFile("fragShader.txt");

	// Cast to char to create shader object
	char* vertC = const_cast<char*>(vert.c_str());
	char* fragC = const_cast<char*>(frag.c_str());

	// Create the actual shader object
	CreateShaderObject(vertC, fragC, &program);
}

#pragma endregion

void GraphicsSystem::InitGLFW(const char* title)
{
	if (!glfwInit())
	{
		yeet new std::exception();
	}

	glfwSetErrorCallback(&error_callback);

	//glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	//glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	window = glfwCreateWindow(width, height, title, NULL, NULL);

	if (!window)
	{
		yeet new std::exception();
	}

	glfwMakeContextCurrent(window);

	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		yeet new std::exception();
	}
}

void GraphicsSystem::InitGL()
{
	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height);
}

void GraphicsSystem::Draw()
{
	std::cout << "Beginning the draw method..." << std::endl;
	while (!glfwWindowShouldClose(window))
	{
		glUseProgram(program);
		for (size_t i = 0; i < batches.size(); i++)
		{
			glBindVertexArray(batches[i].VAO);

			// Need to find the total amount of vertices in a batch
			int numVertices = 0;
			for(size_t j = 0; j < batches[i].objects.size(); j++)
			{
				numVertices += batches[i].objects[j].meshVertices.size();
			}

			glBindBuffer(GL_ARRAY_BUFFER, batches[i].VBO);
			glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * batches[i].objects[i].meshVertices.size(), &batches[i].objects[i].meshVertices[0], GL_DYNAMIC_DRAW);

			// Then call drawarrays with that amount
			glDrawArrays(GL_TRIANGLES, 0, numVertices);
		}
		//glBindVertexArray(0);
		//glUseProgram(0);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	std::cout << "Finished the draw method!" << std::endl;
}

Batch* GraphicsSystem::CreateBatch()
{
	Batch* newBatch = new Batch();
	batches.push_back(*(newBatch));
	std::cout << "New batch created, amount of batches currently: " << batches.size() << std::endl;
	return newBatch;
}