//#define _CRT_SECURE_NO_WARNINGS

#include "Object.h"

Object::Object()
{

}


Object::~Object()
{

}

void Object::LoadOBJ(const char* path)
{
	std::ifstream in(path, std::ios::in);
	if (!in)
	{
		std::cout << "Cannot open " << path << std::endl;
		exit(1);
	}

	std::cout << "Beginning to read the .obj file..." << std::endl;

	std::string line;
	while (std::getline(in, line))
	{
		if (line.substr(0, 2) == "v ")
		{
			std::istringstream v(line.substr(2));
			glm::vec3 vert;
			double x, y, z;
			v >> x;
			v >> y;
			v >> z;
			vert = glm::vec3(x, y, z);
			vertices.push_back(vert);
		}
		else if (line.substr(0, 2) == "vt")
		{
			std::istringstream v(line.substr(3));
			glm::vec2 tex;
			double U, V;
			v >> U;
			v >> V;
			tex = glm::vec2(U, V);
			texture.push_back(tex);
		}
		else if (line.substr(0, 2) == "vn")
		{
			std::istringstream v(line.substr(3));
			glm::vec3 norm;
			double x, y, z;
			v >> x;
			v >> y;
			v >> z;
			norm = glm::vec3(x, y, z);
			normals.push_back(norm);
		}
		else if (line.substr(0, 2) == "f ")
		{
			int a, b, c;
			int A, B, C;
			int D, E, F;
			const char* chh = line.c_str();

			// REMEMBER TO WRITE SOMETHING TO TAKE CARE OF THE FACT THAT A FACE CAN HAVE 3 OR MORE VERTICES
			// MIGHT NEED SOMETHING TO DO WITH OPENGL TRIANGLE STRIPPEDB

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
	}

	std::cout << "Beginning the setting of vertice lists..." << std::endl;

	std::cout << "Size of face indexes: " << faceIndex.size() << std::endl;
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


	std::cout << "Finished the setting of vertice lists..." << std::endl;
}

void Object::Draw()
{

}
