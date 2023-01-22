#ifndef POINT_LIGHT_H
#define POINT_LIGHT_H

#include "Color.h"
#include "Point.h"

class PointLight
{
public:
    PointLight(Color intensity, Point position): intensity(intensity), position(position)
    {

    }

    bool operator==(PointLight const& rhs) const
    {
        double th = 1e-5;
        
        return intensity == rhs.intensity && 
               position == rhs.position;
    }
    
    Color intensity;
    Point position;
};

#endif // POINT_LIGHT_H