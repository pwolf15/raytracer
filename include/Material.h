#ifndef MATERIAL_H
#define MATERIAL_H

#include "Color.h"
#include "Pattern.h"

class Material 
{
public:
    Material(Color color = Color(1.0,1.0,1.0), double ambient = 0.1, double diffuse = 0.9, double specular = 0.9, double shininess = 200.0):
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
    double ambient;
    double diffuse;
    double specular;
    double shininess;
    Pattern pattern;
    
private:
};

#endif // MATERIAL_H