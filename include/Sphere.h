#ifndef SPHERE_H
#define SPHERE_H

#include <vector>

#include "Vector.h"
#include "Ray.h"

class Sphere
{
public:
    Sphere() {}

    std::vector<float> intersect(Ray r)
    {
        std::vector<float> ts;

        Vector sphere_to_ray = r.origin - Point(0, 0, 0);
        float a = r.direction.dot(r.direction);
        float b = 2 * r.direction.dot(sphere_to_ray);
        float c = sphere_to_ray.dot(sphere_to_ray) - 1;
        float discriminant = pow(b,2) - 4*a*c;

        if (discriminant < 0)
        {
            return ts;
        }

        float t1 = (-b - sqrt(discriminant)) / (2 * a);
        float t2 = (-b + sqrt(discriminant)) / (2 * a);

        ts.push_back(t1);
        ts.push_back(t2);
        
        return ts;
    }

private:
};

#endif // SPHERE_H