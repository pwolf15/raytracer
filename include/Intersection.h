#ifndef INTERSECTION_H
#define INTERSECTION_H

#include <optional>

#include "Shape.h"

class Intersection
{
public:

    Intersection(double t, std::shared_ptr<Shape> s): t(t), object(s) {}

    double t;
    std::shared_ptr<Shape> object;
private:

};

#endif // INTERSECTION_H