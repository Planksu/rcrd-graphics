#ifndef _OBJECT_HEADER_
#define _OBJECT_HEADER_

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <glm/glm/glm.hpp>

class Object
{
public:

	Object();
	~Object();
	void LoadOBJ(const char* path);
	void Draw();

public:

	std::vector<glm::vec3> vertices;
	std::vector<glm::vec2> texture;
	std::vector<glm::vec3> normals;
	std::vector<int> faceIndex;
	std::vector<int> textureIndex;
	std::vector<int> normalIndex;

	std::vector<glm::vec3> meshVertices;
	std::vector<glm::vec2> texCoord;
	std::vector<glm::vec3> meshNormals;
};

#endif
