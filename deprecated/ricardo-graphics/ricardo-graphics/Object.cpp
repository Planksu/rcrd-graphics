#define _CRT_SECURE_NO_WARNINGS

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

	for (size_t i = 0; i < faceIndex.size(); i++)
	{
		glm::vec3 meshData;
		glm::vec2 texData;
		glm::vec3 meshNormal;
		meshData = glm::vec3(vertices[faceIndex[i]].x, vertices[faceIndex[i]].y, vertices[faceIndex[i]].z);
		texData = glm::vec2(texture[textureIndex[i]].x, texture[textureIndex[i]].y);
		meshNormal = glm::vec3(normals[normalIndex[i]].x, normals[normalIndex[i]].y, normals[normalIndex[i]].z);
		meshVertices.push_back(meshData);
		texCoord.push_back(texData);
		meshNormals.push_back(meshNormal);
	}
}

void Object::Draw()
{

}
