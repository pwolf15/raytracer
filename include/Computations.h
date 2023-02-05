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

#endif
