#ifndef TEST_SHAPE_H
#define TEST_SHAPE_H

#include "Shape.h"

class TestShape : public Shape
{
public:
    TestShape() {}
    ~TestShape() {}

    void set_transform(Matrix t)
    {
        m_transform = t;
    }

    Vector normal_at(Point pos)
    {
        return Vector(0, 0, 0);
    }
};

#endif // TEST_SHAPE_H