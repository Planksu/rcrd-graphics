#include "Loader.h"

//#define RICARDO_OBJ_LOADING_DEBUG

Loader::Loader()
{

}

void Loader::LoadObj(   const char* path, 
                        std::vector<Object*> &modelObjects,
                        int &objectIndex,
                        std::vector<glm::vec3> &vertices,
                        std::vector<glm::vec2> &texture,
                        std::vector<glm::vec3> &normals)
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
#ifdef RICARDO_OBJ_LOADING_DEBUG            
            std::cout << "This object is: " << objectIndex << std::endl;
            std::cout << "Read vertice contains values: " << x << ", " << y << ", " << z << std::endl;
#endif
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
            std::istringstream v(line.substr(2));
                
            // A .obj file model always starts with atleast one object
            // This is why when creating the first object, we do not need to increment the
            // objectIndex variable
            if(modelObjects.size() != 0)
            {
                objectIndex++;
            }

            // Objects are separated in .obj files by "o <object name>"
            // Create a new object when this line is read
            // Have to get string from istringstream as the representation goes out of scope after this statement
            const std::string tmp = v.str();
            Object* newObject = new Object(tmp.c_str());
            std::cout << "Pushing the new object onto the list.." << std::endl;
            modelObjects.push_back(newObject);
        }
        else if(input == "us")
        {
            // In this case, the line reads "usemtl", which means we have to use the specified material for these faces
            std::istringstream v(line.substr(7));
            const std::string tmp = v.str();
            modelObjects[objectIndex]->material_name = tmp.c_str();
        }
    }
}

void Loader::LoadMtl(const char* path)
{
    std::ifstream in(path, std::ios::in);
    if(!in)
    {
        std::cout << "Cannot open " << path << std::endl;
        exit(-1);
    }

    std::cout << "\nREADING .MTL FILE..." << std::endl;
    std::string line;

    Color ambient = {0};
    Color diffuse = {0};
    Color specular = {0};
    float sp_weight = 0;
    float dissolve = 0;
    float optical_density = 0;
    int illum_model = 0;
    const char* name;

    while(std::getline(in, line))
    {
        std::string input = line.substr(0,2);
        if(input == "ne")
        {
            // New material
            std::istringstream v(line.substr(7));
            const std::string tmp = v.str();
            name = tmp.c_str();
        }
        if(input == "Ns")
        {
            // Specular color exponent, basically weighting
            std::istringstream v(line.substr(3));
            v >> sp_weight;
            std::cout << "Read sp_weight value of: " << sp_weight << std::endl;
        }
        else if(input == "Ka")
        {
            // Ambient color
            std::istringstream v(line.substr(3));
            v >> ambient.r;
            v >> ambient.g;
            v >> ambient.b;
        }
        else if(input == "Kd")
        {
            // Diffuse color
            std::istringstream v(line.substr(3));
            v >> diffuse.r;
            v >> diffuse.g;
            v >> diffuse.b;
        }
        else if(input == "Ks")
        {
            // Specular color
            std::istringstream v(line.substr(3));
            v >> specular.r;
            v >> specular.g;
            v >> specular.b;
        }
        else if(input == "d ")
        {
            // Dissolve factor
            std::istringstream v(line.substr(2));
            v >> dissolve;
        }
        else if(input == "Ni")
        {
            // Optical density
            std::istringstream v(line.substr(3));
            v >> optical_density;
        }
        else if(input == "il")
        {
            // Illumination model
            std::istringstream v(line.substr(6));
            v >> illum_model;
        }
    }

    Material material = Material(ambient, diffuse, specular, sp_weight, dissolve, optical_density, illum_model, name);
}