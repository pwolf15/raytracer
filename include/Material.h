#ifndef MATERIAL_H
#define MATERIAL_H

#include "Color.h"

class Material 
{
public:
    Material(Color color = Color(0.0,0.0,0.0), float ambient = 0.0, float diffuse = 0.0, float specular = 0.0, float shininess = 0.0):
        color(color), ambient(ambient), diffuse(diffuse), specular(specular), shininess(shininess)
    {

    }

    bool operator==(Material const& rhs) const
    {
        double th = 1e-5;
        bool equal = (color == rhs.color) &&
        (abs(ambient - rhs.ambient) < th) && 
        (abs(diffuse - rhs.diffuse) < th) &&
        (abs(specular - rhs.specular) < th) && 
        (abs(shininess - rhs.shininess) < th);
        return equal;
    }

    Color color;
    float ambient;
    float diffuse;
    float specular;
    float shininess;
    
private:
};

#endif // MATERIAL_H