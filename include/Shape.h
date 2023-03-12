#ifndef SHAPE_H
#define SHAPE_H

#include "Material.h"
#include "Matrix.h"

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

    virtual ~Shape() {};

    Matrix m_transform;
    Material m_material;

private:

};

#endif // SHAPE_H