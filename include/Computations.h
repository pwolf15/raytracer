#ifndef COMPUTATIONS_H
#define COMPUTATIONS_H

#include "Point.h"
#include "Sphere.h"
#include "Vector.h"

class Computations
{
public:
    Computations(float t, Sphere* object, Point point, Vector eyev, Vector normalv):  
        m_t(t),
        m_object(object),
        m_point(point),
        m_eyev(eyev),
        m_normalv(normalv)
        {}

    float m_t;
    Sphere* m_object;
    Point m_point;
    Vector m_eyev;
    Vector m_normalv;
private:
};

Computations prepare_computations(Intersection intersection, Ray ray)
{
    float t = intersection.t;
    Sphere* obj = intersection.object;
    Point pos = ray.position(t);
    Computations comps(t, obj, pos, -ray.direction, obj->normal_at(pos));
    return comps;
}

#endif
