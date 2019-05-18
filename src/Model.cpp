#include "Model.h"
#include <sstream>
#include <string>


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
        if(input == "v ")
        {
            std::istringstream v(line.substr(2));
            glm::vec3 vert;
            double x, y, z;
            v >> x; v >> y; v >> z;
            std::cout << "This object is: " << objectIndex << std::endl;
            std::cout << "Read vertice contains values: " << x << ", " << y << ", " << z << std::endl;
            vert = glm::vec3(x, y, z);
            modelObjects[objectIndex]->vertices.push_back(vert);
            vertices.push_back(vert);
        }
        else if(input == "vt")
        {
            std::istringstream v(line.substr(3));
            glm::vec2 tex;
            double U, V;
            v >> U; v >> V;
            tex = glm::vec2(U, V);
            modelObjects[objectIndex]->texture.push_back(tex);
            texture.push_back(tex);
        }
        else if(input == "vn")
        {
            std::istringstream v(line.substr(3));
            glm::vec3 norm;
            double x, y, z;
            v >> x; v >> y; v >> z;
            norm = glm::vec3(x, y, z);
            modelObjects[objectIndex]->normals.push_back(norm);
            normals.push_back(norm);
        }
        else if(input == "f ")
        {
            int a, b, c;
            int A, B, C;
            int D, E, F;
            const char* chh = line.c_str();

            sscanf(chh, "f %i/%i/%i %i/%i/%i %i/%i/%i", &a, &A, &D, &b, &B, &E, &c, &C, &F);
            a--; b--; c--;
            A--; B--; C--;
            D--; E--; F--;

            modelObjects[objectIndex]->faceIndex.push_back(a);
            modelObjects[objectIndex]->faceIndex.push_back(b);
            modelObjects[objectIndex]->faceIndex.push_back(c);

            modelObjects[objectIndex]->textureIndex.push_back(A);
            modelObjects[objectIndex]->textureIndex.push_back(B);
            modelObjects[objectIndex]->textureIndex.push_back(C);

            modelObjects[objectIndex]->normalIndex.push_back(D);
            modelObjects[objectIndex]->normalIndex.push_back(E);
            modelObjects[objectIndex]->normalIndex.push_back(F);

            /*faceIndex.push_back(a);
            faceIndex.push_back(b);
            faceIndex.push_back(c);
            textureIndex.push_back(A);
            textureIndex.push_back(B);
            textureIndex.push_back(C);
            normalIndex.push_back(D);
            normalIndex.push_back(E);
            normalIndex.push_back(F);*/
        }
        else if(input == "o ")
        {
            std::cout << "New object found, creating..." << std::endl;
            
            // A .obj file model always starts with atleast one object
            // This is why when creating the first object, we do not need to increment the
            // objectIndex variable
            if(modelObjects.size() != 0)
            {
                objectIndex++;
            }

            // Objects are separated in .obj files by "o <object name>"
            // Create a new object when this line is read
            Object* newObject = new Object(line.c_str());
            std::cout << "Pushing the new object onto the list.." << std::endl;
            modelObjects.push_back(newObject);
        }
	}

    MatchDataToIndex();
}

// This method creates a default object, as at least one object must be present when a .obj file is read
// Multiple objects may be needed incase the model contains several materials
// ObjectIndex variable will point to the active object, so don't increment it as default value is 0
/*void Model::CreateObject(const char* name)
{
    Object* defaultObject = new Object();
    modelObjects.push_back(defaultObject);
}*/

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

    for(size_t i = 0; i < modelObjects.size(); i++)
    {
        std::cout << "Objects name: " << modelObjects[i]->name << std::endl;
        std::cout << "Object currently being matched: " << i << std::endl;

        std::cout << "Beginning the setting of vertice lists..." << std::endl;

        std::cout << "Size of face indexes: " << modelObjects[i]->faceIndex.size() << std::endl;
        std::cout << "Size of vertices: " << modelObjects[i]->vertices.size() << std::endl;

       /* for(size_t j = 0; j < modelObjects[i]->vertices.size(); j++)
        {
            std::cout << "Vertices in this object:" << modelObjects[i]->vertices[j].x << ", " << modelObjects[i]->vertices[j].y << ", " << modelObjects[i]->vertices[j].z << std::endl;
        }

        for(size_t j = 0; j < modelObjects[i]->faceIndex.size(); j++)
        {
            std::cout << "FaceIndex in this object:" << modelObjects[i]->faceIndex[j] << std::endl;
        }*/

        glm::vec3 meshData;
        glm::vec2 texData;
        glm::vec3 meshNormal;


        for (size_t j = 0; j < modelObjects[i]->faceIndex.size(); j++)
        {
            meshData = glm::vec3(vertices[modelObjects[i]->faceIndex[j]].x, vertices[modelObjects[i]->faceIndex[j]].y, vertices[modelObjects[i]->faceIndex[j]].z);
            //std::cout << "Set mesh data: " << meshData.x << ", " << meshData.y << ", " << meshData.z << std::endl;

            // Create a new vert struct to hold the vertex information
            Vertex newVer = Vertex();
            newVer.vert = meshData;
            vertexes.push_back(newVer);
        }

        std::cout << "Size of texture indexes: " << modelObjects[i]->textureIndex.size() << std::endl;
        for(size_t j = 0; j < modelObjects[i]->textureIndex.size(); j++)
        {
            texData = glm::vec2(texture[modelObjects[i]->textureIndex[j]].x, texture[modelObjects[i]->textureIndex[j]].y);

            // After we created a new vertex struct in the first loop, we can access it with the same indexes here
            vertexes[i].texCoord = texData;
        }
        
        std::cout << "Size of normal indexes: " << modelObjects[i]->normalIndex.size() << std::endl;
        for(size_t j = 0; j < modelObjects[i]->normalIndex.size(); j++)
        {
            meshNormal = glm::vec3(normals[modelObjects[i]->normalIndex[j]].x, normals[modelObjects[i]->normalIndex[j]].y, normals[modelObjects[i]->normalIndex[j]].z);

            // Same thing here
            vertexes[i].norm = meshNormal;
        }

        for(size_t j = 0; j < modelObjects[i]->faceIndex.size(); j++)
        {
            std::cout << "Vertexes content: " << vertexes[j].vert.x << ", " << vertexes[j].vert.y << ", " << vertexes[j].vert.z << std::endl;
        }
        

        std::cout << "Size of vertexes: " << vertexes.size() << std::endl;
        std::cout << "Finished the setting of vertice lists..." << std::endl;
    }	
}