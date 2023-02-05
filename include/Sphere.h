#ifndef SPHERE_H
#define SPHERE_H

#include <vector>

#include "Vector.h"
#include "Ray.h"
#include "Material.h"


class Sphere
{
public:
    Sphere(): transform({
        {1,0,0,0},
        {0,1,0,0},
        {0,0,1,0},
        {0,0,0,1}
    }) {}

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