#include <iostream>
#include <exception>
#include "Object.h"
#include "GraphicsSystem.h"
#include "Batch.h"



int main(int argc, char* argv[])
{
	GraphicsSystem graphics = GraphicsSystem(1280, 720, "Window");

	#ifdef _WIN32
	Batch* cubeBatch = graphics.CreateBatch();
	cubeBatch->LoadObject("C://Users//Antton//Documents//ricardo-graphics//resources//firehydrant.obj", "C://Users//Antton//Documents//ricardo-graphics//resources//firehydrant.mtl");
	#elif defined __linux__
	Batch* cubeBatch = graphics.CreateBatch();
	Batch* millBatch = graphics.CreateBatch();
	millBatch->LoadObject("/home/antton/Documents/ricardo-graphics/mill.obj", "/home/antton/Documents/ricardo-graphics/mill.mtl");
	//cubeBatch->LoadObject("/home/antton/Documents/ricardo-graphics/Cube_tex.obj", "/home/antton/Documents/ricardo-graphics/Cube_tex.mtl");
	#endif

	graphics.Draw();
}