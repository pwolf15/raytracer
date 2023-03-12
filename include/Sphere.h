#ifndef SPHERE_H
#define SPHERE_H

#include <vector>

#include "Material.h"
#include "Ray.h"
#include "Shape.h"
#include "Material.h"

class Sphere: public Shape
{
public:
    Sphere() {}

    void set_transform(Matrix t)
    {
        m_transform = t;
    }

    Vector normal_at(Point p)
    {
        // compute normal by transforming sphere from world to object space
        Point object_point = m_transform.inverse() * p;
        Vector object_normal = object_point - Point(0,0,0);

        // transform normal back to world space using inverse transpose matrix
        Vector world_normal = m_transform.inverse().transpose() * object_normal;
        world_normal.w = 0;
        return world_normal.normalize();
    }

    bool operator==(Sphere const& rhs) const
    {
        double th = 1e-5;
        
        return m_transform == rhs.m_transform && 
            m_material == rhs.m_material;
    }

private:

};

#endif // SPHERE_H