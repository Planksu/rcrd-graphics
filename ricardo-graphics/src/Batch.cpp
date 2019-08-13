#include "Batch.h"
#include <cstddef>

Batch::Batch()
{
}

void Batch::LoadObject(const char* obj_path, const char* mtl_path)
{
	std::cout << "Loading a new model into memory..." << std::endl;
	Model newModel;
	newModel.LoadModel(obj_path, mtl_path);
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

		// Move vertex data to buffers
		glGenBuffers(1, &this->vertexes);
		glBindBuffer(GL_ARRAY_BUFFER, this->vertexes);
		glBufferData(GL_ARRAY_BUFFER, models[i].vertexes.size() * sizeof(Vertex), &models[i].vertexes[0], GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, vert)));
		
		//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);


		// Move normal data to buffers
		//glGenBuffers(1, &this->normals);
		//glBindBuffer(GL_ARRAY_BUFFER, this->normals);
		//glBufferData(GL_ARRAY_BUFFER, models[i].vertexes.size() * sizeof(Vertex), &models[i].vertexes[0], GL_STATIC_DRAW);

		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, norm)));
		//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(glm::vec3)));


		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, texCoord)));
		
		// Unbind
		glBindVertexArray(0);
	}
	std::cout << "Finished generating GL buffers..." << std::endl;
}