#ifndef SPHERE_H
#define SPHERE_H

#include <vector>

#include "Vector.h"
#include "Ray.h"

#include "Intersection.h"

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

        ts.push_back(Intersection(t1, this));
        ts.push_back(Intersection(t2, this));
        
        return ts;
    }

    Matrix transform;
private:

};

#endif // SPHERE_H