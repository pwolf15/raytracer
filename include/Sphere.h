#ifndef SPHERE_H
#define SPHERE_H

#include <vector>

#include "Material.h"
#include "Ray.h"
#include "Shape.h"
#include "Material.h"

class Sphere: public Shape, public std::enable_shared_from_this<Sphere>
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

    std::vector<Intersection> local_intersect(const Ray& r)
    {
        std::vector<Intersection> ts;

        Vector shape_to_ray = r.origin - Point(0, 0, 0);
        double a = r.direction.dot(r.direction);
        double b = 2 * r.direction.dot(shape_to_ray);
        double c = shape_to_ray.dot(shape_to_ray) - 1;
        double discriminant = pow(b,2) - 4*a*c;

        if (discriminant < 0)
        {
            return ts;
        }

        double t1 = (-b - sqrt(discriminant)) / (2 * a);
        double t2 = (-b + sqrt(discriminant)) / (2 * a);

        ts.push_back(Intersection(t1, shared_from_this()));
        ts.push_back(Intersection(t2, shared_from_this()));
        
        return ts;
    }

private:

};

#endif // SPHERE_H