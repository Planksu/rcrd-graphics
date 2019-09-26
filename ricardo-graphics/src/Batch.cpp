#include <Batch.h>
#include <cstddef>


Batch::Batch()
{
}

void Batch::LoadObject(const char* obj_path, const char* mtl_path)
{
	RCRD_DEBUG("Loading a new model into memory...");
	Model newModel;
	newModel.LoadModel(obj_path, mtl_path);
	models.push_back(newModel);
	RCRD_DEBUG("Model loaded to memory, models size now: " << models.size());
	GenerateBuffers();
}

void Batch::GenerateBuffers()
{

	RCRD_DEBUG("GENERATIONG GL BUFFERS...");
	RCRD_DEBUG("Models size when generating bufferes: " << models.size());
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
	RCRD_DEBUG("Finished generating GL buffers!");
}