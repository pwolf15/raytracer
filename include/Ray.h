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

    Ray transform(Matrix m) const
    {
        Ray rT(m*origin, m*direction);
        return rT;
    }

    Point origin;
    Vector direction;

private:

};

#endif // RAY_H