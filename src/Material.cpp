#include "Material.h"

Material::Material(Color am, Color df, Color sp, float sp_weight, float ds, float od, int im, const char* n)
{
    ambient_color = am;
    diffuse_color = df;
    specular_color = sp;
    specular_weight = sp_weight;
    dissolve = ds;
    optical_density = od;
    illum_model = im;
    name = n;
}

