#ifndef INTERSECTION_H
#define INTERSECTION_H

#include "Sphere.h"

class Sphere;

class Intersection
{
public:

    Intersection(float t, Sphere* s): t(t), object(s) {}

    float t;
    Sphere* object;
private:

};

template <class T>
std::vector<Intersection> intersections(std::initializer_list<T> list)
{
    std::vector<Intersection> intersections;
    for (auto elem: list)
    {
        intersections.push_back(elem);
    }

    return intersections;
}

#endif // INTERSECTION_H