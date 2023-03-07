#ifndef COMPUTATIONS_H
#define COMPUTATIONS_H

#include "Point.h"
#include "Sphere.h"
#include "Vector.h"

#define EPSILON 0.00001

class Computations
{
public:
    Computations(double t, std::shared_ptr<Sphere> object, Point point, Point over_point, Vector eyev, Vector normalv, bool inside):  
        m_t(t),
        m_object(object),
        m_point(point),
        m_over_point(over_point),
        m_eyev(eyev),
        m_normalv(normalv),
        m_inside(inside)
        {}

    double m_t;
    std::shared_ptr<Sphere> m_object;
    Point m_point;
    Point m_over_point;
    Vector m_eyev;
    Vector m_normalv;
    bool m_inside;

private:
};

#endif
