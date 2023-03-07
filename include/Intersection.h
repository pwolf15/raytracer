#ifndef INTERSECTION_H
#define INTERSECTION_H

#include <optional>

#include "Sphere.h"

class Intersection
{
public:

    Intersection(double t, std::shared_ptr<Sphere> s): t(t), object(s) {}

    double t;
    std::shared_ptr<Sphere> object;
private:

};

#endif // INTERSECTION_H