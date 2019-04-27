#include "Model.h"

Model::Model()
{
    objectIndex = 0;
}

// This method loads the entire .obj files vertices, texcoords and normals into memory
// This is not to be confused with Object-class, which contains all vertices, texcoords and normals for a portion
// of the model that is to be drawn with a material
void Model::LoadModel(const char* path)
{
    // Check that our .obj file exists
    std::ifstream in(path, std::ios::in);
	if (!in)
	{
		std::cout << "Cannot open " << path << std::endl;
		exit(1);
	}

	std::cout << "\nREADING .OBJ FILE..." << std::endl;
	std::string line;

	while (std::getline(in, line))
	{
        std::string input = line.substr(0,2);
        switch(input)
        {
            case "v ":
            {
                std::istringstream v(line.substr(2));
                glm::vec3 vert;
                double x, y, z;
                v >> x; v >> y; v >> z;
                vert = glm::vec3(x, y, z);
                vertices.push_back(vert);
                break;
            }
            case "vt":
            {
                std::istringstream v(line.substr(3));
                glm::vec2 tex;
                double U, V;
                v >> U; v >> V;
                tex = glm::vec2(U, V);
                texture.push_back(tex);
                break;
            }
            case "vn":
            {
                std::istringstream v(line.substr(3));
                glm::vec3 norm;
                double x, y, z;
                v >> x; v >> y; v >> z;
                norm = glm::vec3(x, y, z);
                normals.push_back(norm);
                break;
            }
            case "f ":
            {
                int a, b, c;
                int A, B, C;
                int D, E, F;
                const char* chh = line.c_str();

                sscanf(chh, "f %i/%i/%i %i/%i/%i %i/%i/%i", &a, &A, &D, &b, &B, &E, &c, &C, &F);
                a--; b--; c--;
                A--; B--; C--;
                D--; E--; F--;
                faceIndex.push_back(a);
                faceIndex.push_back(b);
                faceIndex.push_back(c);
                textureIndex.push_back(A);
                textureIndex.push_back(B);
                textureIndex.push_back(C);
                normalIndex.push_back(D);
                normalIndex.push_back(E);
                normalIndex.push_back(F);
            }
            case "o ":
            {
                // Objects are separated in .obj files by "o <object name>"
                // Create a new object when this line is read
                Object* newObject = new Object();
                modelObjects.push_back(*(newObject));
                objectIndex++;
            }
        }
	}

    MatchDataToIndex();
}

// This method creates a default object, as at least one object must be present when a .obj file is read
// Multiple objects may be needed incase the model contains several materials
// ObjectIndex variable will point to the active object, so don't increment it as default value is 0
void Model::CreateObject(const char* name)
{
    Object* defaultObject = new Object();
    modelObjects.push_back(defaultObject);
}

// This method matches the read vertice, texturecoordinate and normals data to their correct face indexes read
// from the face data contained in the .obj file
void Model::MatchDataToIndex()
{
    // First, check that we have atleast one object
    if(modelObjects.size() == 0)
    {
        std::cout << "No objects created while still trying to read .obj file, ceasing read..." << std::endl;
        exit(1);
    }
    // Then get a reference to the current object that we will store this .obj data in
    Object* currentObject = modelObjects[objectIndex];

	std::cout << "Beginning the setting of vertice lists..." << std::endl;

	std::cout << "Size of face indexes: " << faceIndex.size() << std::endl;
	std::cout << "Size of vertices: " << vertices.size() << std::endl;
	for (size_t i = 0; i < faceIndex.size(); i++)
	{
		glm::vec3 meshData;
		meshData = glm::vec3(vertices[faceIndex[i]].x, vertices[faceIndex[i]].y, vertices[faceIndex[i]].z);
		meshVertices.push_back(meshData);
	}

	std::cout << "Size of texture indexes: " << textureIndex.size() << std::endl;
	for(size_t i = 0; i < textureIndex.size(); i++)
	{
		glm::vec2 texData;
		texData = glm::vec2(texture[textureIndex[i]].x, texture[textureIndex[i]].y);
		texCoord.push_back(texData);
	}
	
	std::cout << "Size of normal indexes: " << normalIndex.size() << std::endl;
	for(size_t i = 0; i < normalIndex.size(); i++)
	{
		glm::vec3 meshNormal;
		meshNormal = glm::vec3(normals[normalIndex[i]].x, normals[normalIndex[i]].y, normals[normalIndex[i]].z);
		meshNormals.push_back(meshNormal);
	}
	
	std::cout << "Size of meshVertices: " << meshVertices.size() << std::endl;
	std::cout << "Size of texCoord: " << texCoord.size() << std::endl;
	std::cout << "Size of meshNormals: " << meshNormals.size() << std::endl;

	for(size_t i = 0; i < meshVertices.size(); i++)
	{
		std::cout << meshVertices[i].x << " " << meshVertices[i].y << " " << meshVertices[i].z << std::endl;
	}
	std::cout << "Finished the setting of vertice lists..." << std::endl;
}