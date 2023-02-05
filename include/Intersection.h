#ifndef INTERSECTION_H
#define INTERSECTION_H

#include <optional>

#include "Sphere.h"

class Intersection
{
public:

    Intersection(float t, Sphere& s): t(t), object(s) {}

    float t;
    Sphere object;
private:

};

#endif // INTERSECTION_H