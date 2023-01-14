#ifndef MATERIAL_H
#define MATERIAL_H

#include "Color.h"

class Material 
{
public:
    Material(Color color, float ambient, float diffuse, float specular, float shininess):
        color(color), ambient(ambient), diffuse(diffuse), specular(specular), shininess(shininess)
    {

    }

    Color color;
    float ambient;
    float diffuse;
    float specular;
    float shininess;
    
private:
};

#endif // MATERIAL_H