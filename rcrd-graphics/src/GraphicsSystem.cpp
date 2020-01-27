#include <GraphicsSystem.h>
#include <glm/gtx/string_cast.hpp>


#define GLM_ENABLE_EXPERIMENTAL


GraphicsSystem::GraphicsSystem(int w, int h, const char* title)
{
	width = w; height = h;
	InitGLFW(title);
	InitGL();
	InitShaders();
	InitLight();
	InitCamera();
}

GraphicsSystem::~GraphicsSystem()
{
}

void error_callback(int error, const char* description)
{
	fprintf(stderr, "Error: %s\n", description);
}

#pragma region Shader methods

void GraphicsSystem::InitShaders()
{
	shader = new Shader();
	std::string vert = shader->LoadShaderFromFile("shaders/vertShader.glsl");
	std::string frag = shader->LoadShaderFromFile("shaders/fragShader.glsl");
	shader->CreateShaderObject(vert, frag);
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
	glm::vec3 position = glm::vec3(-10.f, 10.f, 10.0f);
	glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f);
	glm::vec3 ambient_color = glm::vec3(0.0f, 0.0f, 0.2f);
	glm::vec3 direction = glm::vec3(0.0f, 0.0f, 0.0f);
	float shininess = 5.f;

	light = new Light(position, color, ambient_color, direction, shininess);
}

void GraphicsSystem::InitCamera()
{
	glm::vec3 position = glm::vec3(0.f, -1.f, -2.f);
	glm::vec3 rotation = glm::vec3(0.3f, 0.f, 0.f);
	float fov = 90.f;
	camera = new Camera(position, rotation, fov);
}

void GraphicsSystem::Draw()
{
	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		RCRD_DEBUG("Batches size: " << batches.size());
		glUseProgram(shader->program);

		// Make some kind of angles to use in rotating
		static float r = 0;
		r += 0.00016f * 90;

		glm::mat4 model = glm::mat4(1.0f);
		// Translate a bit forward
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -5.0f));
		// and the rotation
		model = glm::rotate(model, r, glm::vec3(0.0f, 1.0f, 0.0f));

		glm::mat4 view = glm::mat4(1.0f);

		view = glm::translate(view, camera->pos);
		view = glm::rotate(view, camera->rot.x, glm::vec3(1.0f, 0.0f, 0.0f));
		view = glm::rotate(view, camera->rot.y, glm::vec3(0.0f, 1.0f, 0.0f));
		view = glm::rotate(view, camera->rot.z, glm::vec3(0.0f, 0.0f, 1.0f));

		light->direction = view * glm::vec4(light->direction, 1.0f);

		glm::mat4 projection = glm::perspective(45.f, (float)width / (float)height, 1.0f, 2000.0f);
		glm::mat4 mvp = projection * view * model;
		glm::mat4 mv = model * view;
		glm::mat4 mv_inverse_transpose = glm::transpose(glm::inverse(mv));
		glUniformMatrix4fv(glGetUniformLocation(shader->program, "mvp"), 1, GL_FALSE, (const GLfloat*)&mvp[0]);
		glUniformMatrix4fv(glGetUniformLocation(shader->program, "mv"), 1, GL_FALSE, (const GLfloat*)&mv[0]);
		glUniform3f(glGetUniformLocation(shader->program, "u_light_position"), light->position.x, light->position.y, light->position.z);
		glUniform3f(glGetUniformLocation(shader->program, "u_light_color"), light->color.x, light->color.y, light->color.z);
		glUniform3f(glGetUniformLocation(shader->program, "u_ambient_color"), light->ambient_color.x, light->ambient_color.y, light->ambient_color.z);
		glUniform3f(glGetUniformLocation(shader->program, "camera_position"), camera->pos.x, camera->pos.y, camera->pos.z);
		glUniform3f(glGetUniformLocation(shader->program, "u_light_dir"), light->direction.x, light->direction.y, light->direction.z);
		glUniform1f(glGetUniformLocation(shader->program, "u_shininess"), light->shininess);
		GLint vertexColorLocation = glGetUniformLocation(shader->program, "color");

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