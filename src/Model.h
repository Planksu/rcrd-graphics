#ifndef _MODEL_HEADER_
#define _MODEL_HEADER_

#include "Object.h"
#include <vector>


// This class is a container for all the objects that a model could have
// As a model can be constructed of several objects that all have to be separated to keep materials
// operational, this class keeps all of a single models information collected in one place
class Model
{
public:
    Model();
    void LoadModel(const char* path);
    void CreateObject(const char* name);
    void MatchDataToIndex();

public:
    std::vector<Object*> modelObjects;
    int objectIndex;

	// The entire model vertices, textures and normals
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec2> texture;
	std::vector<glm::vec3> normals;

    std::vector<glm::vec3> meshVertices;
	std::vector<glm::vec2> texCoord;
	std::vector<glm::vec3> meshNormals;

};

#endif
