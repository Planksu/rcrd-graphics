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

	Object(const char* n);

public:
	const char* name;

	// Index lists
	std::vector<int> faceIndex;
	std::vector<int> textureIndex;
	std::vector<int> normalIndex;

	// The vertices, coords and normals to be drawn with the material of this object
	std::vector<glm::vec3> meshVertices;
	std::vector<glm::vec2> texCoord;
	std::vector<glm::vec3> meshNormals;

	// Temporary holders
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec2> texture;
	std::vector<glm::vec3> normals;
};

#endif
