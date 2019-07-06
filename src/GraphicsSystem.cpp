#include "GraphicsSystem.h"
#include <glm/glm/gtx/string_cast.hpp>

#define GLM_ENABLE_EXPERIMENTAL


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
			printf("Error linking program:\n%s\n", infoLog);

			free(infoLog);
		}

		glDeleteProgram(*object);
		return;
	}


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

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

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
	std::cout << "GL VERSION\n" << std::endl;
	std::cout << glGetString(GL_VERSION) << std::endl;
}

void GraphicsSystem::Draw()
{
	std::cout << "Beginning the draw method..." << std::endl;
	while (!glfwWindowShouldClose(window))
	{
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		std::cout << "Batches size: " << batches.size() << std::endl;
		glUseProgram(program);

		// Make some kind of angles to use in rotating
		static float r = 0;
		r += 0.00016f * 90;

		glm::mat4 model = glm::mat4(1.0f);
		// Translate a bit forward
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -5.0f));
		// and the rotation
		model = glm::rotate(model, r, glm::vec3(0.0f, 1.0f, 0.0f));

		glm::mat4 view = glm::mat4(1.0f);
		glm::mat4 projection = glm::perspective(45.f, (float)width / (float)height, 1.0f, 10.0f);
		glm::mat4 mvp = projection * view * model;
		glUniformMatrix4fv(glGetUniformLocation(program, "mvp"), 1, GL_FALSE, (const GLfloat*)&mvp[0]);

		for (size_t i = 0; i < batches.size(); i++)
		{
			std::cout << "Models size: " << batches[i]->models.size() << std::endl;

			glBindVertexArray(batches[i]->VAO);

			// Need to find the total amount of vertices in a batch
			int numVertices = 0;
			for(size_t j = 0; j < batches[i]->models.size(); j++)
			{
				numVertices += batches[i]->models[j].vertexes.size();
			}
			// Then call drawarrays with that amount
			std::cout << "Right before draw call" << std::endl;
			std::cout << "Number of vertices: " << numVertices << std::endl;
			glDrawArrays(GL_TRIANGLES, 0, numVertices);

			glBindVertexArray(0);
		}
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	std::cout << "Finished the draw method!" << std::endl;
}

Batch* GraphicsSystem::CreateBatch()
{
	Batch* newBatch = new Batch();
	batches.push_back(newBatch);
	std::cout << "New batch created, amount of batches currently: " << batches.size() << std::endl;
	return newBatch;
}