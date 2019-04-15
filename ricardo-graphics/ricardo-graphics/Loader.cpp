#define _CRT_SECURE_NO_WARNINGS

#include "Loader.h"

Loader::Loader()
{

}


Loader::~Loader()
{

}

void Loader::LoadOBJ(const char* path)
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
			int U, V;
			v >> U;
			v >> V;
			tex = glm::vec2(U, V);
			texture.push_back(tex);
		}
		else if (line.substr(0, 2) == "f ")
		{
			int a, b, c;
			int A, B, C;
			const char* chh = line.c_str();

			// REMEMBER TO WRITE SOMETHING TO TAKE CARE OF THE FACT THAT A FACE CAN HAVE 3 OR MORE VERTICES
			// MIGHT NEED SOMETHING TO DO WITH OPENGL TRIANGLE STRIPPEDB


			sscanf(chh, "f %i//%i %i//%i %i//%i", &a, &A, &b, &B, &c, &C);
			a--; b--; c--;
			A--; B--; C--;
			faceIndex.push_back(a);
			faceIndex.push_back(b);
			faceIndex.push_back(c);
			textureIndex.push_back(A);
			textureIndex.push_back(B);
			textureIndex.push_back(C);
		}
	}

	for (size_t i = 0; i < faceIndex.size(); i++)
	{
		glm::vec3 meshData;
		//glm::vec2 texData;
		meshData = glm::vec3(vertices[faceIndex[i]].x, vertices[faceIndex[i]].y, vertices[faceIndex[i]].z);
		//texData = glm::vec2(texture[textureIndex[i]].x, texture[textureIndex[i]].y);
		meshVertices.push_back(meshData);
		//texCoord.push_back(texData);
	}
}
