#include <Loader.h>


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
		RCRD_DEBUG("Cannot open " << path);
        exit(-1);
    }
	RCRD_DEBUG("\nREADING .OBJ FILE...");
    
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
            vert = glm::vec3(x, y, z);

			RCRD_DEBUG("This object is: " << objectIndex);
			RCRD_DEBUG("Read vertice contains values: " << x << ", " << y << ", " << z);
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
            int d, e, f;
            int g, h, i;
            const char* chh = line.c_str();

			// Read all vertice indexes with one line
            sscanf(chh, "f %i/%i/%i %i/%i/%i %i/%i/%i", &a, &d, &g, &b, &e, &h, &c, &f, &i);
            a--; b--; c--;
            d--; e--; f--;
            g--; h--; i--;

            modelObjects[objectIndex]->faceIndex.push_back(a);
            modelObjects[objectIndex]->faceIndex.push_back(b);
            modelObjects[objectIndex]->faceIndex.push_back(c);

            modelObjects[objectIndex]->textureIndex.push_back(d);
            modelObjects[objectIndex]->textureIndex.push_back(e);
            modelObjects[objectIndex]->textureIndex.push_back(f);

            modelObjects[objectIndex]->normalIndex.push_back(g);
            modelObjects[objectIndex]->normalIndex.push_back(h);
            modelObjects[objectIndex]->normalIndex.push_back(i);
        }
        else if(input == "o ")
        {
			RCRD_DEBUG("New object found, creating...");
            std::istringstream v(line.substr(2));
                
            // A .obj file model always starts with atleast one object
            // This is why when creating the first object, we do not need to increment the
            // objectIndex variable, as the index for the first object should be 0
            if(modelObjects.size() != 0)
            {
                objectIndex++;
            }

            // Objects are separated in .obj files by "o <object name>"
            // Create a new object when this line is read
            // Have to get string from istringstream as the representation goes out of scope after this statement
            const std::string tmp = v.str();
            Object* newObject = new Object(tmp.c_str());
			RCRD_DEBUG("Pushing the new object onto the list...");
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

void Loader::LoadMtl(const char* path, std::vector<Material*> &modelMaterials, int materialIndex)
{
    std::ifstream in(path, std::ios::in);
    if(!in)
    {
		RCRD_DEBUG("Cannot open " << path);
        exit(-1);
    }

	RCRD_DEBUG("\nREADING .MTL FILE...");
    
	std::string line;
    Color ambient = {0};
    Color diffuse = {0};
    Color specular = {0};
    float sp_weight = 0;
    float dissolve = 0;
    float optical_density = 0;
    int illum_model = 0;
    std::string name;

    while(std::getline(in, line))
    {
        std::string input = line.substr(0,2);
        if(input == "ne")
        {
            // New material
            std::istringstream v(line.substr(7));
            name = v.str();

            if(modelMaterials.size() != 0)
            {
                materialIndex++;
            }

            Material* newMaterial = new Material(ambient, diffuse, specular, sp_weight, dissolve, optical_density, illum_model, name);
            modelMaterials.push_back(newMaterial);
        }
        if(input == "Ns")
        {
            // Specular color exponent, basically weighting
            std::istringstream v(line.substr(3));
            v >> modelMaterials[materialIndex]->specular_weight;
        }
        else if(input == "Ka")
        {
            // Ambient color
            std::istringstream v(line.substr(3));

            v >> modelMaterials[materialIndex]->ambient_color.r;
            v >> modelMaterials[materialIndex]->ambient_color.g;
            v >> modelMaterials[materialIndex]->ambient_color.b;
        }
        else if(input == "Kd")
        {
            // Diffuse color
            std::istringstream v(line.substr(3));
            v >> modelMaterials[materialIndex]->diffuse_color.r;
            v >> modelMaterials[materialIndex]->diffuse_color.g;
            v >> modelMaterials[materialIndex]->diffuse_color.b;
        }
        else if(input == "Ks")
        {
            // Specular color
            std::istringstream v(line.substr(3));
            v >> modelMaterials[materialIndex]->specular_color.r;
            v >> modelMaterials[materialIndex]->specular_color.g;
            v >> modelMaterials[materialIndex]->specular_color.b;
        }
        else if(input == "d ")
        {
            // Dissolve factor
            std::istringstream v(line.substr(2));
            v >> modelMaterials[materialIndex]->dissolve;
        }
        else if(input == "Ni")
        {
            // Optical density
            std::istringstream v(line.substr(3));
            v >> modelMaterials[materialIndex]->optical_density;
        }
        else if(input == "il")
        {
            // Illumination model
            std::istringstream v(line.substr(6));
            v >> modelMaterials[materialIndex]->illum_model;
        }
    }
}