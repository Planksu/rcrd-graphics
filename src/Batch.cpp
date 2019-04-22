#include "Batch.h"

Batch::Batch()
{
    currentVAOIndex = 1;
}

void Batch::LoadObject(const char* path)
{
	std::cout << "Loading a new object into memory..." << std::endl;
	Object newObject;
	newObject.LoadOBJ(path);
	objects.push_back(newObject);
	GenerateBuffers();
}

void Batch::GenerateBuffers()
{
	std::cout << "Generating GL buffers..." << std::endl;
	for (size_t i = 0; i < objects.size(); i++)
	{
        // VAO stuff
		glGenVertexArrays(1, &this->VAO);
		glBindVertexArray(this->VAO);

        // VBO stuff
        glGenBuffers(1, &this->VBO);
		//glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
        //glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * objects[i].meshVertices.size(), &objects[i].meshVertices[0], GL_DYNAMIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
		glEnableVertexAttribArray(0);

        // Unbind
        glBindVertexArray(0);
	}
	std::cout << "Finished generating GL buffers..." << std::endl;
}