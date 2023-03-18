#ifndef TEST_SHAPE_H
#define TEST_SHAPE_H

#include "Ray.h"
#include "Shape.h"

class TestShape : public Shape, public std::enable_shared_from_this<TestShape>
{
public:
    TestShape(): m_saved_ray(Point(0,0,0), Vector(0,0,0)) {}

    void set_transform(Matrix t)
    {
        m_transform = t;
    }

    Vector normal_at(Point pos)
    {
        return Vector(pos.x, pos.y, pos.z);
    }

    std::vector<Intersection> local_intersect(const Ray& r)
    {
        std::vector<Intersection> ts;

        m_saved_ray = r;

        return ts;
    }

    Ray m_saved_ray;

};

#endif // TEST_SHAPE_H