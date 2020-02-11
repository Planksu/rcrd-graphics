#include <Object.h>
#include <GraphicsSystem.h>
#include <InputSystem.h>
#include <Batch.h>

#include <iostream>
#include <exception>


int main(int argc, char* argv[])
{
	GraphicsSystem graphics = GraphicsSystem(1280, 720, "rcrd_graphics");
	InputSystem input = InputSystem(1280 / 2, 720 / 2);

	#ifdef _WIN32
	Batch* monkeyBatch = graphics.CreateBatch();
	monkeyBatch->LoadObject("./resources/monkey.obj", "./resources/monkey.mtl");
	Batch* floorBatch = graphics.CreateBatch();
	floorBatch->LoadObject("./resources/floor.obj", "./resources/floor.mtl");
	Batch* cubeBatch = graphics.CreateBatch();
	cubeBatch->LoadObject("./resources/cube.obj", "./resources/cube.mtl");
	Batch* ballBatch = graphics.CreateBatch();
	ballBatch->LoadObject("./resources/ball.obj", "./resources/ball.mtl");
	Batch* cylinderBatch = graphics.CreateBatch();
	cylinderBatch->LoadObject("./resources/cylinder.obj", "./resources/cylinder.mtl");
	#elif defined __linux__
	#endif

	while (!glfwWindowShouldClose(graphics.window))
	{
		graphics.Update();
		input.Update(graphics.window, graphics.camera);
	}
}