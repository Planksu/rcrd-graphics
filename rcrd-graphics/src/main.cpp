#include <Object.h>
#include <GraphicsSystem.h>
#include <Batch.h>

#include <iostream>
#include <exception>


int main(int argc, char* argv[])
{
	GraphicsSystem graphics = GraphicsSystem(1280, 720, "rcrd_graphics");

	#ifdef _WIN32
	//Batch* monkeyBatch = graphics.CreateBatch();
	//monkeyBatch->LoadObject("./resources/cubesmooth.obj", "./resources/cubesmooth.mtl");
	//monkeyBatch->diffuse = glm::vec3(0.2f, 0.2f, 0.8f);
	//monkeyBatch->specular = glm::vec3(0.7f, 0.7f, 0.7f);
	Batch* floorBatch = graphics.CreateBatch();
	floorBatch->LoadObject("./resources/cube2.obj", "./resources/cube2.mtl");
	floorBatch->diffuse = glm::vec3(0.2f, 0.8f, 0.2f);
	floorBatch->specular = glm::vec3(0.5f, 0.5f, 0.5f);
	Batch* cubeBatch = graphics.CreateBatch();
	cubeBatch->LoadObject("./resources/cube.obj", "./resources/cube.mtl");
	cubeBatch->diffuse = glm::vec3(0.8f, 0.2f, 0.2f);
	cubeBatch->specular = glm::vec3(0.5f, 0.5f, 0.5f);
	Batch* ballBatch = graphics.CreateBatch();
	ballBatch->LoadObject("./resources/ball.obj", "./resources/ball.mtl");
	ballBatch->diffuse = glm::vec3(0.8f, 0.2f, 0.8f);
	ballBatch->specular = glm::vec3(0.5f, 0.5f, 0.5f);
	#elif defined __linux__
	#endif


	graphics.Draw();
}