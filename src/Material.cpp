#include "Material.h"

Material::Material(Color am, Color df, Color sp, float sp_weight, float ds)
{
    ambient_color = am;
    diffuse_color = df;
    specular_color = sp;
    specular_weight = sp_weight;
    dissolve = ds;
}

