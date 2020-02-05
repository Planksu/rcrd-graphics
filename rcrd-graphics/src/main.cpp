#include <Object.h>
#include <GraphicsSystem.h>
#include <Batch.h>

#include <iostream>
#include <exception>


int main(int argc, char* argv[])
{
	GraphicsSystem graphics = GraphicsSystem(1280, 720, "rcrd_graphics");

	#ifdef _WIN32
	Batch* monkeyBatch = graphics.CreateBatch();
	monkeyBatch->LoadObject("./resources/cubesmooth.obj", "./resources/cubesmooth.mtl");
	Batch* floorBatch = graphics.CreateBatch();
	floorBatch->LoadObject("./resources/cube2.obj", "./resources/cube2.mtl");
	Batch* cubeBatch = graphics.CreateBatch();
	cubeBatch->LoadObject("./resources/floor.obj", "./resources/floor.mtl");
	Batch* ballBatch = graphics.CreateBatch();
	ballBatch->LoadObject("./resources/ball.obj", "./resources/ball.mtl");
	#elif defined __linux__
	#endif


	graphics.Draw();
}