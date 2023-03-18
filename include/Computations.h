#ifndef COMPUTATIONS_H
#define COMPUTATIONS_H

#include "Constants.h"
#include "Point.h"
#include "Shape.h"
#include "Vector.h"

class Computations
{
public:
    Computations(double t, std::shared_ptr<Shape> object, Point point, Point over_point, Vector eyev, Vector normalv, bool inside):  
        m_t(t),
        m_object(object),
        m_point(point),
        m_over_point(over_point),
        m_eyev(eyev),
        m_normalv(normalv),
        m_inside(inside)
        {}

    double m_t;
    std::shared_ptr<Shape> m_object;
    Point m_point;
    Point m_over_point;
    Vector m_eyev;
    Vector m_normalv;
    bool m_inside;

private:
};

#endif
