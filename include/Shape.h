#ifndef SHAPE_H
#define SHAPE_H

#include <vector>

#include "Intersection.h"
#include "Material.h"
#include "Matrix.h"
#include "Point.h"
#include "Ray.h"
#include "Vector.h"

class Shape
{
public:

    Shape(): m_transform({
        {1,0,0,0},
        {0,1,0,0},
        {0,0,1,0},
        {0,0,0,1}
    }) {}

    virtual void set_transform(Matrix t) = 0;

    virtual Vector normal_at(Point pos) = 0;

    virtual std::vector<Intersection> local_intersect(const Ray& r) = 0;

    virtual ~Shape() {};

    Matrix m_transform;
    Material m_material;

private:

};

#endif // SHAPE_H