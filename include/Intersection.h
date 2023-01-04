#ifndef INTERSECTION_H
#define INTERSECTION_H

#include <optional>

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

std::optional<Intersection> hit(std::vector<Intersection>& xs)
{
    std::vector<Intersection> xs_copy;
    std::copy_if(xs.begin(), xs.end(), std::back_inserter(xs_copy), [](Intersection i) {
        return i.t >= 0;
    });

    std::sort(xs_copy.begin(), xs_copy.end(), [](Intersection a, Intersection b) {
        return a.t < b.t;
    });
    return !xs_copy.empty() ? std::optional<std::reference_wrapper<Intersection>>(xs_copy[0]) : std::nullopt;
}

#endif // INTERSECTION_H