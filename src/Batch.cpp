#include "Batch.h"

Batch::Batch()
{
}

void Batch::LoadObject(const char* path)
{
	std::cout << "Loading a new model into memory..." << std::endl;
	Model newModel;
	newModel.LoadModel(path);
	models.push_back(newModel);
	std::cout << "Model loaded to memory, models size now: " << models.size() << std::endl;
	GenerateBuffers();
}

void Batch::GenerateBuffers()
{
	std::cout << "\nGENERATING GL BUFFERS..." << std::endl;
	std::cout << "Models size when generating buffers: " << models.size() << std::endl;
	for (size_t i = 0; i < models.size(); i++)
	{
		// VAO stuff
		glGenVertexArrays(1, &this->VAO);
		glBindVertexArray(this->VAO);

		// VBO stuff
		glGenBuffers(1, &this->VBO);
		glBindBuffer(GL_ARRAY_BUFFER, this->VBO);

		std::cout << "Buffer data generated" << std::endl;

		glBufferData(GL_ARRAY_BUFFER, models[i].vertexes.size() * sizeof(Vertex), &models[i].vertexes[0], GL_STATIC_DRAW);
		//glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
		//glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * objects[i].meshVertices.size(), &objects[i].meshVertices[0], GL_DYNAMIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), nullptr);

		// Unbind
		glBindVertexArray(0);
    
	}
	std::cout << "Finished generating GL buffers..." << std::endl;
}