#ifndef SPHERE_H
#define SPHERE_H

#include <vector>

#include "Vector.h"
#include "Ray.h"
#include "Intersection.h"
#include "Material.h"

class Intersection;

class Sphere
{
public:
    Sphere(): transform({
        {1,0,0,0},
        {0,1,0,0},
        {0,0,1,0},
        {0,0,0,1}
    }) {}

    std::vector<Intersection> intersect(Ray r)
    {
        std::vector<Intersection> ts;

        Matrix inv = transform.inverse();
        Ray ray2 = r.transform(inv);
        Vector sphere_to_ray = ray2.origin - Point(0, 0, 0);
        float a = ray2.direction.dot(ray2.direction);
        float b = 2 * ray2.direction.dot(sphere_to_ray);
        float c = sphere_to_ray.dot(sphere_to_ray) - 1;
        float discriminant = pow(b,2) - 4*a*c;

        if (discriminant < 0)
        {
            return ts;
        }

        float t1 = (-b - sqrt(discriminant)) / (2 * a);
        float t2 = (-b + sqrt(discriminant)) / (2 * a);

        ts.push_back(Intersection(t1, this));
        ts.push_back(Intersection(t2, this));
        
        return ts;
    }

    void set_transform(Matrix t)
    {
        transform = t;
    }

    Vector normal_at(Point p)
    {
        // compute normal by transforming sphere from world to object space
        Point object_point = transform.inverse() * p;
        Vector object_normal = object_point - Point(0,0,0);

        // transform normal back to world space using inverse transpose matrix
        Vector world_normal = transform.inverse().transpose() * object_normal;
        world_normal.w = 0;
        return world_normal.normalize();
    }

    bool operator==(Sphere const& rhs) const
    {
        double th = 1e-5;
        
        return transform == rhs.transform && 
            material == rhs.material;
    }


    Matrix transform;
    Material material;
private:

};

#endif // SPHERE_H