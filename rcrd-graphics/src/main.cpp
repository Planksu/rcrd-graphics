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
<<<<<<< HEAD:ricardo-graphics/src/main.cpp
	cubeBatch->LoadObject("./resources/Teekanne001.obj", "./resources/Teekanne001.mtl");
=======
	cubeBatch->LoadObject("./resources/monkeysmooth.obj", "./resources/monkeysmooth.mtl");
>>>>>>> fbcb9da439dd558e4fdce42084fd9fab3ef5271f:rcrd-graphics/src/main.cpp
	#elif defined __linux__
	#endif


	graphics.Draw();
}