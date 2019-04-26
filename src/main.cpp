#include <iostream>
#include <exception>
#include "Object.h"
#include "GraphicsSystem.h"
#include "Batch.h"



int main(int argc, char* argv[])
{
	GraphicsSystem graphics = GraphicsSystem(640, 480, "Window");

	#ifdef _WIN32
	Batch* cubeBatch = graphics.LoadObject("fill in windows path");
	#elif defined __linux__
	Batch* cubeBatch = graphics.CreateBatch();
	cubeBatch->LoadObject("/home/antton/Documents/ricardo-graphics/mill.obj");
	#endif

	graphics.Draw();
}