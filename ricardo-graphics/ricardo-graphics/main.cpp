#include <iostream>
#include <exception>
#include "Object.h"
#include "GraphicsSystem.h"



int main(int argc, char* argv[])
{
	GraphicsSystem graphics = GraphicsSystem(640, 480, "Window");

	graphics.LoadOBJ("C://Users//anttonjok//Documents//ricardo-graphics//Cube.obj");
	
	graphics.Draw();
}