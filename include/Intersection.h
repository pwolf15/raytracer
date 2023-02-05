#ifndef INTERSECTION_H
#define INTERSECTION_H

#include <optional>

#include "Sphere.h"

class Intersection
{
public:

    Intersection(float t, std::shared_ptr<Sphere> s): t(t), object(s) {}

    float t;
    std::shared_ptr<Sphere> object;
private:

};

#endif // INTERSECTION_H