#include <GraphicsSystem.h>
#include <glm/gtx/string_cast.hpp>


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
			RCRD_DEBUG("Error compiling shader: " << infoLog);
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
			RCRD_DEBUG("Error linking program: " << infoLog);

			free(infoLog);
		}

		glDeleteProgram(*object);
		return;
	}


	return;
}

void GraphicsSystem::InitShaders()
{
	std::string vert = LoadShaderFromFile("shaders/vertShader.glsl");
	std::string frag = LoadShaderFromFile("shaders/fragShader.glsl");

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
		exit(-1);
	}

	glfwSetErrorCallback(&error_callback);

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(width, height, title, NULL, NULL);

	if (!window)
	{
		exit(-1);
	}

	glfwMakeContextCurrent(window);

	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		exit(-1);
	}
}

void GraphicsSystem::InitGL()
{
	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height);
	RCRD_DEBUG("GL VERSION " << glGetString(GL_VERSION));
	glEnable(GL_DEPTH_TEST);
}

void GraphicsSystem::InitLight()
{
	glm::vec3 position = glm::vec3(50000.0f, 5000.0f, 3.0f);
	glm::vec3 color = glm::vec3(1.0f, 0.0f, 0.0f);
	glm::vec3 ambient_color = glm::vec3(0.2f, 0.2f, 0.2f);
	float shininess = 0.1f;

	light = new Light(position, color, ambient_color, shininess);
}

void GraphicsSystem::Draw()
{
	while (!glfwWindowShouldClose(window))
	{
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		RCRD_DEBUG("Batches size: " << batches.size());
		glUseProgram(program);
		// Make some kind of angles to use in rotating
		static float r = 0;
		r += 0.00016f * 90;

		glm::mat4 model = glm::mat4(1.0f);
		// Translate a bit forward
		model = glm::translate(model, glm::vec3(0.0f, -0.5f, -5.0f));
		// and the rotation
		model = glm::rotate(model, r, glm::vec3(0.0f, 1.0f, 0.0f));

		glm::mat4 view = glm::mat4(1.0f);
		glm::mat4 projection = glm::perspective(45.f, (float)width / (float)height, 1.0f, 10.0f);
		glm::mat4 mvp = projection * view * model;
		glm::mat4 mv = model * view;
		glm::mat4 mv_inverse_transpose = glm::transpose(glm::inverse(mv));
		glUniformMatrix4fv(glGetUniformLocation(program, "mvp"), 1, GL_FALSE, (const GLfloat*)&mvp[0]);
		glUniformMatrix4fv(glGetUniformLocation(program, "mv"), 1, GL_FALSE, (const GLfloat*)&mv[0]);
		glUniform3f(glGetUniformLocation(program, "u_light_position"), light->position.x, light->position.y, light->position.z);
		glUniform3f(glGetUniformLocation(program, "u_light_color"), light->color.x, light->color.y, light->color.z);
		glUniform3f(glGetUniformLocation(program, "u_ambient_color"), light->ambient_color.x, light->ambient_color.y, light->ambient_color.z);
		glUniform1f(glGetUniformLocation(program, "u_shininess"), light->shininess);
		GLint lightPos = glGetUniformLocation(program, "u_light_position");
		GLint vertexColorLocation = glGetUniformLocation(program, "color");

		for (size_t i = 0; i < batches.size(); i++)
		{
			RCRD_DEBUG("Models size: " << batches[i]->models.size());
			glBindVertexArray(batches[i]->VAO);
			for (int j = 0; j < batches[i]->models.size(); ++j)
			{
				int numVertices = 0;
				int prevNum = 0;
				for (int k = 0; k < batches[i]->models[j].modelObjects.size(); ++k)
				{
					RCRD_DEBUG("Size of objects vertices: " << batches[i]->models[j].modelObjects[k]->vertexes.size());
					RCRD_DEBUG("Size of models vertices: " << batches[i]->models[j].vertexes.size());
		
					numVertices += (batches[i]->models[j].modelObjects[k]->vertexes.size());
					glUniform3f(vertexColorLocation, batches[i]->models[j].modelObjects[k]->mat->diffuse_color.r,  batches[i]->models[j].modelObjects[k]->mat->diffuse_color.g,  batches[i]->models[j].modelObjects[k]->mat->diffuse_color.b);
					glDrawArrays(GL_TRIANGLES, prevNum, numVertices);

					prevNum = numVertices;
				}
			}
			glBindVertexArray(0);
		}
		glfwPollEvents();
		glfwSwapBuffers(window);
		RCRD_DEBUG("Finished the draw method!");
	}
}

Batch* GraphicsSystem::CreateBatch()
{
	Batch* newBatch = new Batch();
	batches.push_back(newBatch);
	RCRD_DEBUG("New batch created, amount of batches currently: " << batches.size());
	return newBatch;
}