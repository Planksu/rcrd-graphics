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
	mainShader = new Shader();
	depthShader = new Shader();
	//std::string vert = mainShader->LoadShaderFromFile("shaders/vertShader.glsl");
	//std::string frag = mainShader->LoadShaderFromFile("shaders/fragShader.glsl");
	std::string vert = mainShader->LoadShaderFromFile("shaders/depthVert.glsl");
	std::string frag = mainShader->LoadShaderFromFile("shaders/depthFrag.glsl");
	std::string vertDepth = mainShader->LoadShaderFromFile("shaders/depthMapVert.glsl");
	std::string fragDepth = mainShader->LoadShaderFromFile("shaders/depthMapFrag.glsl");

	mainShader->CreateShaderObject(vert, frag);
	depthShader->CreateShaderObject(vertDepth, fragDepth);
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
	glm::vec3 position = glm::vec3(5.f, 5.f, 5.0f);
	glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f);
	glm::vec3 ambient_color = glm::vec3(0.0f, 0.0f, 0.2f);
	glm::vec3 direction = glm::vec3(0.0f, 0.f, 0.f);
	float shininess = 5.f;

	light = new Light(position, color, ambient_color, direction, shininess);
}

void GraphicsSystem::InitCamera()
{
	glm::vec3 position = glm::vec3(0.f, -2.f, -4.f);
	glm::vec3 rotation = glm::vec3(0.f, 0.f, 0.f);
	float fov = 90.f;
	camera = new Camera(position, rotation, fov);
}

void GraphicsSystem::CreateShadowMap()
{
	glm::mat4 lightProj, lightView;
	float near = 1.0f, far = 50.f;
	lightProj = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, near, far);
	lightView = glm::lookAt(light->position, glm::vec3(0.0f), glm::vec3(0.0, 1.0, 0.0));
	lightSpaceMatrix = lightProj * lightView;

	glUseProgram(depthShader->program);
	glUniformMatrix4fv(glGetUniformLocation(depthShader->program, "lightSpaceMatrix"), 1, GL_FALSE, (const GLfloat*)&lightSpaceMatrix[0]);
	
	glViewport(0, 0, SHADOW_WIDTH, SHADOW_HEIGHT);
	glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
	glClear(GL_DEPTH_BUFFER_BIT);

	//render
	// Make some kind of angles to use in rotating
	static float r = 0;
	r += 0.00016f * 90;

	glm::mat4 model = glm::mat4(1.0f);
	// Translate a bit forward
	model = glm::translate(model, glm::vec3(0.0f, 0.0f, -5.0f));
	// and the rotation
	model = glm::rotate(model, r, glm::vec3(0.0f, 1.0f, 0.0f));

	glUniformMatrix4fv(glGetUniformLocation(depthShader->program, "model"), 1, GL_FALSE, (const GLfloat*)&model[0]);
	glUniformMatrix4fv(glGetUniformLocation(depthShader->program, "lightSpaceMatrix"), 1, GL_FALSE, (const GLfloat*)&lightSpaceMatrix[0]);

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
				glDrawArrays(GL_TRIANGLES, prevNum, numVertices);

				prevNum = numVertices;
			}
		}
		glBindVertexArray(0);
	}

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glViewport(0, 0, width, height);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void GraphicsSystem::Draw()
{
	glGenFramebuffers(1, &depthMapFBO);
	glUseProgram(depthShader->program);

	glGenTextures(1, &depthMap);
	glBindTexture(GL_TEXTURE_2D, depthMap);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT,
		SHADOW_WIDTH, SHADOW_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthMap, 0);
	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	glUseProgram(mainShader->program);


	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		CreateShadowMap();

		RCRD_DEBUG("Batches size: " << batches.size());
		glUseProgram(mainShader->program);

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
		glUniform3f(glGetUniformLocation(mainShader->program, "viewPos"), camera->pos.x, camera->pos.y, camera->pos.z);
		glUniform3f(glGetUniformLocation(mainShader->program, "lightPos"), light->position.x, light->position.y, light->position.z);
		glUniformMatrix4fv(glGetUniformLocation(mainShader->program, "projection"), 1, GL_FALSE, (const GLfloat*)&projection[0]);
		glUniformMatrix4fv(glGetUniformLocation(mainShader->program, "model"), 1, GL_FALSE, (const GLfloat*)&model[0]);
		glUniformMatrix4fv(glGetUniformLocation(mainShader->program, "view"), 1, GL_FALSE, (const GLfloat*)&view[0]);
		glUniformMatrix4fv(glGetUniformLocation(mainShader->program, "lightSpaceMatrix"), 1, GL_FALSE, (const GLfloat*)&lightSpaceMatrix[0]);
		glUniform1i(glGetUniformLocation(mainShader->program, "diffuseTexture"), 0);
		glUniform1i(glGetUniformLocation(mainShader->program, "shadowMap"), 1);

		//glUniformMatrix4fv(glGetUniformLocation(mainShader->program, "mvp"), 1, GL_FALSE, (const GLfloat*)&mvp[0]);
		//glUniformMatrix4fv(glGetUniformLocation(mainShader->program, "mv"), 1, GL_FALSE, (const GLfloat*)&mv[0]);
		//glUniformMatrix4fv(glGetUniformLocation(mainShader->program, "m"), 1, GL_FALSE, (const GLfloat*)&model[0]);
		//glUniform3f(glGetUniformLocation(mainShader->program, "u_light_position"), light->position.x, light->position.y, light->position.z);
		//glUniform3f(glGetUniformLocation(mainShader->program, "u_light_color"), light->color.x, light->color.y, light->color.z);
		//glUniform3f(glGetUniformLocation(mainShader->program, "u_ambient_color"), light->ambient_color.x, light->ambient_color.y, light->ambient_color.z);
		//glUniform3f(glGetUniformLocation(mainShader->program, "camera_position"), camera->pos.x, camera->pos.y, camera->pos.z);
		//glUniform3f(glGetUniformLocation(mainShader->program, "u_light_dir"), light->direction.x, light->direction.y, light->direction.z);
		//glUniform1f(glGetUniformLocation(mainShader->program, "u_shininess"), light->shininess);
		//GLint vertexDiffuseLocation = glGetUniformLocation(mainShader->program, "diffuse");
		//GLint vertexAmbientLocation = glGetUniformLocation(mainShader->program, "ambient");
		//GLint vertexSpecularLocation = glGetUniformLocation(mainShader->program, "specular");


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
					/*glUniform3f(vertexDiffuseLocation, batches[i]->models[j].modelObjects[k]->mat->diffuse_color.r,  batches[i]->models[j].modelObjects[k]->mat->diffuse_color.g,  batches[i]->models[j].modelObjects[k]->mat->diffuse_color.b);
					glUniform3f(vertexAmbientLocation, batches[i]->models[j].modelObjects[k]->mat->ambient_color.r, batches[i]->models[j].modelObjects[k]->mat->ambient_color.g, batches[i]->models[j].modelObjects[k]->mat->ambient_color.b);
					glUniform3f(vertexSpecularLocation, batches[i]->models[j].modelObjects[k]->mat->specular_color.r, batches[i]->models[j].modelObjects[k]->mat->specular_color.g, batches[i]->models[j].modelObjects[k]->mat->specular_color.b);
					glUniform3f(glGetUniformLocation(mainShader->program, "diffuse_model"), batches[i]->diffuse.x, batches[i]->diffuse.y, batches[i]->diffuse.z);
					glUniform3f(glGetUniformLocation(mainShader->program, "specular_model"), batches[i]->specular.x, batches[i]->specular.y, batches[i]->specular.z);*/
					glActiveTexture(GL_TEXTURE0);
					glBindTexture(GL_TEXTURE_2D, depthMap);

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