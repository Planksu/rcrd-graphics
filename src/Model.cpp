#include "Model.h"
#include "Material.h"
#include "Loader.h"
#include <sstream>
#include <string>

//#define RICARDO_OBJ_MATCHING_DEBUG

Model::Model()
{
    objectIndex = 0;
}

// This method loads the entire .obj files vertices, texcoords and normals into memory
// This is not to be confused with Object-class, which contains all vertices, texcoords and normals for a portion
// of the model that is to be drawn with a material
void Model::LoadModel(const char* obj_path, const char* mtl_path)
{
    Loader loader = Loader();
    loader.LoadObj(obj_path, modelObjects, objectIndex, vertices, texture, normals);
 //   loader.LoadMtl(mtl_path);
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
        exit(-1);
    }

    for(size_t i = 0; i < modelObjects.size(); i++)
    {
#ifdef RICARDO_OBJ_MATCHING_DEBUG
        std::cout << "Objects name: " << modelObjects[i]->name << std::endl;
        std::cout << "Object currently being matched: " << i << std::endl;

        std::cout << "Beginning the setting of vertice lists..." << std::endl;

        std::cout << "Size of face indexes: " << modelObjects[i]->faceIndex.size() << std::endl;
        std::cout << "Size of vertices: " << modelObjects[i]->vertices.size() << std::endl;
#endif

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
#ifdef RICARDO_OBJ_MATCHING_DEBUG
        std::cout << "Size of texture indexes: " << modelObjects[i]->textureIndex.size() << std::endl;
#endif
        for(size_t j = 0; j < modelObjects[i]->textureIndex.size(); j++)
        {
            texData = glm::vec2(texture[modelObjects[i]->textureIndex[j]].x, texture[modelObjects[i]->textureIndex[j]].y);

            // After we created a new vertex struct in the first loop, we can access it with the same indexes here
            vertexes[i].texCoord = texData;
        }
#ifdef RICARDO_OBJ_MATCHING_DEBUG  
        std::cout << "Size of normal indexes: " << modelObjects[i]->normalIndex.size() << std::endl;
#endif
        for(size_t j = 0; j < modelObjects[i]->normalIndex.size(); j++)
        {
            meshNormal = glm::vec3(normals[modelObjects[i]->normalIndex[j]].x, normals[modelObjects[i]->normalIndex[j]].y, normals[modelObjects[i]->normalIndex[j]].z);

            // Same thing here
            vertexes[i].norm = meshNormal;
        }

#ifdef RICARDO_OBJ_MATCHING_DEBUG
        for(size_t j = 0; j < modelObjects[i]->faceIndex.size(); j++)
        {
            std::cout << "Vertexes content: " << vertexes[j].vert.x << ", " << vertexes[j].vert.y << ", " << vertexes[j].vert.z << std::endl;
        }
        std::cout << "Size of vertexes: " << vertexes.size() << std::endl;
        std::cout << "Finished the setting of vertice lists..." << std::endl;
#endif
    }	
}