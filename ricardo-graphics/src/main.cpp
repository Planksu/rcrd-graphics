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
	//cubeBatch->LoadObject("C://Users//Antton//Documents//ricardo-graphics//resources//firehydrant.obj", "C://Users//Antton//Documents//ricardo-graphics//resources//firehydrant.mtl");
	cubeBatch->LoadObject("./resources/monkey.obj", "./resources/monkey.mtl");
	#elif defined __linux__
	#endif


	graphics.Draw();
}