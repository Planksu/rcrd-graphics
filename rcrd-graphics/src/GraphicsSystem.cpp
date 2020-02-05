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
	std::string vert = mainShader->LoadShaderFromFile("shaders/pointLightShaderV.glsl");
	std::string frag = mainShader->LoadShaderFromFile("shaders/pointLightShaderF.glsl");
	std::string vertDepth = depthShader->LoadShaderFromFile("shaders/depthVert.glsl");
	std::string fragDepth = depthShader->LoadShaderFromFile("shaders/depthFrag.glsl");
	std::string geomDepth = depthShader->LoadShaderFromFile("shaders/depthGeom.glsl");


	mainShader->CreateShaderObject(vert, frag);
	depthShader->CreateShaderObject(vertDepth, fragDepth, geomDepth);
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

void GLAPIENTRY
MessageCallback(GLenum source,
	GLenum type,
	GLuint id,
	GLenum severity,
	GLsizei length,
	const GLchar* message,
	const void* userParam)
{
	fprintf(stderr, "GL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s\n",
		(type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : ""),
		type, severity, message);
}

void GraphicsSystem::InitGL()
{
	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height);
	RCRD_DEBUG("GL VERSION " << glGetString(GL_VERSION));
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_DEBUG_OUTPUT);
	glDebugMessageCallback(MessageCallback, 0);
}

void GraphicsSystem::InitLight()
{
	glm::vec3 position = glm::vec3(0.f, 5.f, 0.f);
	glm::vec3 color = glm::vec3(0.5f, 0.5f, 0.5f);
	glm::vec3 ambient_color = glm::vec3(0.0f, 0.0f, 0.2f);
	float shininess = 5.f;

	light = new Light(position, color, ambient_color, shininess);
}

void GraphicsSystem::InitCamera()
{
	glm::vec3 position = glm::vec3(0.f, -2.f, -5.f);
	glm::vec3 rotation = glm::vec3(0.3f, 0.f, 0.f);
	float fov = 90.f;
	camera = new Camera(position, rotation, fov);
}

void GraphicsSystem::CreateShadowMap()
{
	light->position.x = sin(glfwGetTime()) * 3.0f;
	light->position.z = cos(glfwGetTime()) * 5.0f;
	
	glm::mat4 shadowProj = glm::perspective(glm::radians(90.f), (float)SHADOW_WIDTH / (float)SHADOW_HEIGHT, near, far);
	std::vector<glm::mat4> shadowTransforms;
	shadowTransforms.push_back(shadowProj * glm::lookAt(light->position, light->position + glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f)));
	shadowTransforms.push_back(shadowProj * glm::lookAt(light->position, light->position + glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f)));
	shadowTransforms.push_back(shadowProj * glm::lookAt(light->position, light->position + glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f)));
	shadowTransforms.push_back(shadowProj * glm::lookAt(light->position, light->position + glm::vec3(0.0f, -1.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f)));
	shadowTransforms.push_back(shadowProj * glm::lookAt(light->position, light->position + glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, -1.0f, 0.0f)));
	shadowTransforms.push_back(shadowProj * glm::lookAt(light->position, light->position + glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, -1.0f, 0.0f)));

	std::vector<GLchar*> names;
	names.push_back("shadowMatrices[0]");
	names.push_back("shadowMatrices[1]");
	names.push_back("shadowMatrices[2]");
	names.push_back("shadowMatrices[3]");
	names.push_back("shadowMatrices[4]");
	names.push_back("shadowMatrices[5]");
	
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(0.0f, 0.0f, -5.0f));

	glViewport(0, 0, SHADOW_WIDTH, SHADOW_HEIGHT);
	glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
	glClear(GL_DEPTH_BUFFER_BIT);
	glUseProgram(depthShader->program);

	for (size_t i = 0; i < 6; i++)
	{
		depthShader->SetMat4Uniform(names[i], shadowTransforms[i]);
	}
	depthShader->SetFloatUniform("far_plane", far);
	depthShader->SetVec3Uniform("lightPos", light->position);
	depthShader->SetMat4Uniform("model", model);

	RenderScene(depthShader, RENDER_MODE::DEPTH);
}

void GraphicsSystem::Draw()
{
	glUseProgram(depthShader->program);
	glGenFramebuffers(1, &depthMapFBO);
	glGenTextures(1, &depthCubemap);
	glBindTexture(GL_TEXTURE_CUBE_MAP, depthCubemap);
	for (size_t i = 0; i < 6; i++)
	{
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_DEPTH_COMPONENT,
			SHADOW_WIDTH, SHADOW_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
	}
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	
	glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
	glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, depthCubemap, 0);
	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	glUseProgram(mainShader->program);


	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		CreateShadowMap();

		RCRD_DEBUG("Batches size: " << batches.size());
		glUseProgram(mainShader->program);

		glDisable(GL_CULL_FACE);
		RenderScene(mainShader, RENDER_MODE::FRAGMENT);
		glEnable(GL_CULL_FACE);


		glfwPollEvents();
		glfwSwapBuffers(window);
		RCRD_DEBUG("Finished the draw method!");
		RCRD_DEBUG("Error amount:" << glGetError());
	}
}

void GraphicsSystem::RenderScene(Shader* shader, RENDER_MODE mode)
{
	glm::mat4 model = glm::mat4(1.0f);
	glm::mat4 view = glm::mat4(1.0f);

	// Translate a bit forward
	model = glm::translate(model, glm::vec3(0.0f, 0.0f, -5.0f));

	// Make view = camera position
	view = glm::translate(view, camera->pos);

	// Take care of possible rotations
	view = glm::rotate(view, camera->rot.x, glm::vec3(1.0f, 0.0f, 0.0f));
	view = glm::rotate(view, camera->rot.y, glm::vec3(0.0f, 1.0f, 0.0f));
	view = glm::rotate(view, camera->rot.z, glm::vec3(0.0f, 0.0f, 1.0f));

	glm::mat4 projection = glm::perspective(45.f, (float)width / (float)height, near, far);
	glm::mat4 mvp = projection * view * model;
	glm::mat4 mv = model * view;

	shader->SetVec3Uniform("lightPos", light->position);
	shader->SetMat4Uniform("model", model);
	shader->SetFloatUniform("far_plane", far);

	
	// These uniforms only need to be set when rendering the actual lighted scene
	if (mode == RENDER_MODE::FRAGMENT)
	{
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_CUBE_MAP, depthCubemap);
		shader->SetVec3Uniform("viewPos", camera->pos);
		shader->SetMat4Uniform("projection", projection);
		shader->SetMat4Uniform("view", view);
		shader->SetIntUniform("depthMap", 1);
		shader->SetVec3Uniform("lightColor", light->color);
		shader->SetVec3Uniform("lightAmbient", light->ambient_color);
	}


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
				shader->SetVec3Uniform("diffuse", batches[i]->models[j].modelObjects[k]->mat->diffuse_color);
				glDrawArrays(GL_TRIANGLES, prevNum, numVertices);

				prevNum = numVertices;
			}
		}
		glBindVertexArray(0);
	}

	// Also, these only need to be set when rendering depthmap
	if (mode == RENDER_MODE::DEPTH)
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glViewport(0, 0, width, height);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}
}

Batch* GraphicsSystem::CreateBatch()
{
	Batch* newBatch = new Batch();
	batches.push_back(newBatch);
	RCRD_DEBUG("New batch created, amount of batches currently: " << batches.size());
	return newBatch;
}