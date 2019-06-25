#ifndef _LOADER_H
#define _LOADER_H

#include <vector>
#include "Object.h"
#include <sstream>
#include <string>

#include <glm/glm/glm.hpp>

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
    void LoadMtl(const char* path);

};

#endif