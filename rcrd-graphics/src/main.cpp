#include <Object.h>
#include <GraphicsSystem.h>
#include <Batch.h>

#include <iostream>
#include <exception>


int main(int argc, char* argv[])
{
	GraphicsSystem graphics = GraphicsSystem(1280, 720, "rcrd_graphics");

	#ifdef _WIN32
	Batch* cubeBatch = graphics.CreateBatch();
	cubeBatch->LoadObject("./resources/cubesmooth.obj", "./resources/cubesmooth.mtl");
	Batch* floorBatch = graphics.CreateBatch();
	floorBatch->LoadObject("./resources/floor.obj", "./resources/floor.mtl");
	#elif defined __linux__
	#endif


	graphics.Draw();
}