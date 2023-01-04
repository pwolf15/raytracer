#ifndef RAY_H
#define RAY_H

#include "Point.h"
#include "Vector.h"

class Ray
{
public:
    Ray(Point origin, Vector direction): origin(origin), direction(direction) 
        {}

    Point position(float t)
    {
        return origin + direction * t;
    }

    Point origin;
    Vector direction;

private:

};

Ray transform(Ray r, Matrix m)
{
    Ray rT(m*r.origin, m*r.direction);
    return rT;
}

#endif // RAY_H