#ifndef PLANE_H
#define PLANE_H

#include "Constants.h"
#include "Matrix.h"
#include "Shape.h"
#include "Ray.h"
#include "Intersection.h"
#include "Utils.h"

class Plane: public Shape, public std::enable_shared_from_this<Plane>
{
public:
    Plane() {}

    void set_transform(Matrix t)
    {
        m_transform = t;
    }

    Vector normal_at(Point p)
    {
        // planned assumed to be a plane in xz
        return Vector(0, 1, 0);
    }

    std::vector<Intersection> local_intersect(const Ray& r)
    {
        if (abs(r.direction.y) < EPSILON)
        {
            return {};
        }
        else
        {
            float t = -r.origin.y / r.direction.y;
            return { Intersection(t, shared_from_this()) };
        }
    }
};

#endif // PLANE_H