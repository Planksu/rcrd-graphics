#ifndef RCRD_LOADER_H
#define RCRD_LOADER_H

#include <Object.h>
#include <Material.h>
#include <core.h>

#include <vector>
#include <sstream>
#include <string>

#include <glm/glm.hpp>

class Loader
{
public:
    Loader();

    void LoadObj(   const char* path,
                    std::vector<Object*> &modelObjects,
                    int &objectIndex, 
                    std::vector<glm::vec3> &vertices, 
                    std::vector<glm::vec2> &texture, 
                    std::vector<glm::vec3> &normals);
    void LoadMtl(	const char* path,
    				std::vector<Material*> &modelMaterials,
    				int materialIndex);

};

#endif