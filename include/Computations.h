#ifndef COMPUTATIONS_H
#define COMPUTATIONS_H

#include "Point.h"
#include "Sphere.h"
#include "Vector.h"

class Computations
{
public:
    Computations(float t, Sphere* object, Point point, Vector eyev, Vector normalv, bool inside):  
        m_t(t),
        m_object(object),
        m_point(point),
        m_eyev(eyev),
        m_normalv(normalv),
        m_inside(inside)
        {}

    float m_t;
    Sphere* m_object;
    Point m_point;
    Vector m_eyev;
    Vector m_normalv;
    bool m_inside;

private:
};

Computations prepare_computations(Intersection intersection, Ray ray)
{
    float t = intersection.t;
    Sphere* obj = intersection.object;
    Point pos = ray.position(t);
    Vector eyev = -ray.direction, normalv = obj->normal_at(pos);
    bool inside = false;

    // check if intersection occurs on inside of object
    if (normalv.dot(eyev) < 0)
    {
        inside = true;
        normalv = -normalv;
    }
    
    Computations comps(t, obj, pos, eyev, normalv, inside);
    return comps;
}

#endif
