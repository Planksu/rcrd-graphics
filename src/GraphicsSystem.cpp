#include "GraphicsSystem.h"
#include <glm/glm/gtx/string_cast.hpp>


#define GLM_ENABLE_EXPERIMENTAL
//#define RICARDO_RUNTIME_DEBUG


GraphicsSystem::GraphicsSystem(int w, int h, const char* title)
{
	width = w; height = h;
	InitGLFW(title);
	InitGL();
	InitShaders();
	InitLight();
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

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
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

void GraphicsSystem::InitLight()
{
	glm::vec3 position = glm::vec3(0.0f, -2.0f, -2.0f);
	glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f);
	glm::vec3 ambient_color = glm::vec3(0.2f, 0.2f, 0.2f);
	float shininess = 0.1f;

	light = new Light(position, color, ambient_color, shininess);
}

void GraphicsSystem::Draw()
{
	while (!glfwWindowShouldClose(window))
	{
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

#ifdef RICARDO_RUNTIME_DEBUG
		std::cout << "Batches size: " << batches.size() << std::endl;
#endif
		glUseProgram(program);

		// Make some kind of angles to use in rotating
		static float r = 0;
		r += 0.00016f * 90;

		glm::mat4 model = glm::mat4(1.0f);
		// Translate a bit forward
		model = glm::translate(model, glm::vec3(0.0f, -0.5f, -2.0f));
		// and the rotation
		model = glm::rotate(model, r, glm::vec3(0.0f, 1.0f, 0.0f));

		glm::mat4 view = glm::mat4(1.0f);
		glm::mat4 projection = glm::perspective(45.f, (float)width / (float)height, 1.0f, 10.0f);
		glm::mat4 mvp = projection * view * model;
		glm::mat4 mv = model * view;
		glUniformMatrix4fv(glGetUniformLocation(program, "mvp"), 1, GL_FALSE, (const GLfloat*)&mvp[0]);
		glUniformMatrix4fv(glGetUniformLocation(program, "mv"), 1, GL_FALSE, (const GLfloat*)&mv[0]);
		glUniform3f(glGetUniformLocation(program, "u_light_position"), light->position.x, light->position.y, light->position.z);
		glUniform3f(glGetUniformLocation(program, "u_light_color"), light->color.x, light->color.y, light->color.z);
		glUniform3f(glGetUniformLocation(program, "u_ambient_color"), light->ambient_color.x, light->ambient_color.y, light->ambient_color.z);
		glUniform1f(glGetUniformLocation(program, "u_shininess"), light->shininess);

		int vertexColorLocation = glGetUniformLocation(program, "color");

		for (size_t i = 0; i < batches.size(); i++)
		{
#ifdef RICARDO_RUNTIME_DEBUG
			std::cout << "Models size: " << batches[i]->models.size() << std::endl;
#endif
			glBindVertexArray(batches[i]->VAO);
			for (int j = 0; j < batches[i]->models.size(); ++j)
			{
				int numVertices = 0;
				int prevNum = 0;
				for (int k = 0; k < batches[i]->models[j].modelObjects.size(); ++k)
				{
#ifdef RICARDO_RUNTIME_DEBUG
					std::cout << "Size of objects vertices: " << batches[i]->models[j].modelObjects[k]->vertexes.size() << std::endl;
					std::cout << "Size of models vertices: " << batches[i]->models[j].vertexes.size() << std::endl;
#endif
					numVertices += (batches[i]->models[j].modelObjects[k]->vertexes.size());
					
					glUniform3f(vertexColorLocation, batches[i]->models[j].modelObjects[k]->mat->diffuse_color.r,  batches[i]->models[j].modelObjects[k]->mat->diffuse_color.g,  batches[i]->models[j].modelObjects[k]->mat->diffuse_color.b);
					//std::cout << "Diffuse color: " << batches[i]->models[j].modelObjects[k]->mat->diffuse_color.r << std::endl;
					glDrawArrays(GL_TRIANGLES, prevNum, numVertices);

					prevNum = numVertices;
				}
			}
			glBindVertexArray(0);
		}
		glfwPollEvents();
		glfwSwapBuffers(window);

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