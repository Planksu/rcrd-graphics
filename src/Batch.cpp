#include "Batch.h"

Batch::Batch()
{
}

void Batch::LoadObject(const char* path)
{
	std::cout << "Loading a new object into memory..." << std::endl;
	Object newObject;
	newObject.LoadOBJ(path);
	objects.push_back(newObject);
	std::cout << "Object loaded to memory, objects size now: " << objects.size() << std::endl;
	GenerateBuffers();
}

void Batch::GenerateBuffers()
{
	std::cout << "\nGENERATING GL BUFFERS..." << std::endl;
	std::cout << "Objects size when generating buffers: " << objects.size() << std::endl;
	for (size_t i = 0; i < objects.size(); i++)
	{
        // VAO stuff
		glGenVertexArrays(1, &this->VAO);
		glBindVertexArray(this->VAO);

        // VBO stuff
        glGenBuffers(1, &this->VBO);
		glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
		glBufferData(GL_ARRAY_BUFFER, objects[i].meshVertices.size() * sizeof(float) * 3, &objects[i].meshVertices[0], GL_STATIC_DRAW);

		//glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
        //glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * objects[i].meshVertices.size(), &objects[i].meshVertices[0], GL_DYNAMIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, nullptr);

        // Unbind
        glBindVertexArray(0);
	}
	std::cout << "Finished generating GL buffers..." << std::endl;
}