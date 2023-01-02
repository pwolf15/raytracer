#ifndef RAY_H
#define RAY_H

#include "Point.h"
#include "Vector.h"

class Ray
{
public:
    Ray(Point origin, Vector direction): origin(origin), direction(direction) 
        {}

    Point origin;
    Vector direction;
    
private:

};

#endif // RAY_H