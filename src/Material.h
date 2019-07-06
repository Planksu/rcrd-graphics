#ifndef _MATERIAL_H
#define _MATERIAL_H

struct Color
{
   float r;
   float g;
   float b; 
};

enum illum_models
{
    COLOR_ON_AMBIENT_OFF = 0,
    COLOR_ON_AMBIENT_ON = 1,
    HIGHLIGHT_ON = 2,
    REFLECTION_ON_RAY_TRACE_ON = 3,
    TRANSPARENCY_GLASS_ON_REFLECTION_RAY_TRACE_ON = 4,
    REFLECTION_FRESNEL_ON_RAY_TRACE_ON = 5,
    TRANSPARENCY_REFRACTION_ON_REFLECTION_FRESNEL_OFF_RAY_TRACE_ON = 6,
    TRANSPARENCY_REFRACTION_ON_REFLECTION_FRESNEL_ON_RAY_TRACE_ON = 7,
    REFLECTION_ON_RAY_TRACE_OFF = 8,
    TRANSPARENCY_GLASS_ON_REFLECTION_RAY_TRACE_OFF = 9,
    CAST_SHADOWS_ONTO_INVISIBLE_SURFACES = 10
} ;

class Material
{
public:
    Material(Color am, Color df, Color sp, float sp_weight, float ds, float od,  int im);


private:
    Color ambient_color;
    Color diffuse_color;

    Color specular_color;
    float specular_weight;  // Specular weight varies between 0-1000

    float dissolve;         // Dissolve variable, basically like transparency but not quite

    float optical_density;  // Determines how light is refracted

    int illum_model;        // Illumination model


};


#endif