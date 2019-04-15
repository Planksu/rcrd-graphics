#ifndef _LOADER_HEADER_
#define _LOADER_HEADER_

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <GLFW/glfw3.h>
#include <glm.hpp>

class Loader
{
public:

	Loader();
	~Loader();
	void LoadOBJ(const char* path);

public:

	std::vector<glm::vec3> vertices;
	std::vector<glm::vec2> texture;
	std::vector<int> faceIndex;
	std::vector<int> textureIndex;

	std::vector<glm::vec3> meshVertices;
	std::vector<glm::vec2> texCoord;
};

#endif
