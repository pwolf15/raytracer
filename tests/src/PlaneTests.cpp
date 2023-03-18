#include "CppUTest/CommandLineTestRunner.h"

#include "Plane.h"
#include "TestUtils.h"
#include "Transformations.h"
#include "Utils.h"
#include "Vector.h"

TEST_GROUP(Plane)
{

};

TEST(Plane, NormalAt)
{
    Plane p;
    Vector n1 = p.normal_at(Point(0,0,0));
    Vector n2 = p.normal_at(Point(10,0,-10));
    Vector n3 = p.normal_at(Point(-5,0,150));
    CHECK(Vector(0,1,0) == n1);
    CHECK(Vector(0,1,0) == n2);
    CHECK(Vector(0,1,0) == n3);
}

TEST(Plane, Intersect)
{
    // Intersect with a ray parallel to the plane
    Ray r(Point(0,10,0), Vector(0,0,1));
    std::shared_ptr<Plane> p = std::make_shared<Plane>();
    std::vector<Intersection> xs = p->local_intersect(r);
    CHECK(xs.empty());

    // Intersect with a coplanar ray
    r = Ray(Point(0,0,0), Vector(0,0,1));
    xs = p->local_intersect(r);
    CHECK(xs.empty());

    // Intersecting a plane from above
    r = Ray(Point(0,1,0), Vector(0,-1,0));
    xs = p->local_intersect(r);
    CHECK_EQUAL(1, xs.size());
    CHECK_EQUAL(1, xs[0].t);

    // Intersecting a plane from below
    r = Ray(Point(0,-1,0), Vector(0, 1, 0));
    xs = p->local_intersect(r);
    CHECK_EQUAL(1, xs.size());
    CHECK_EQUAL(1, xs[0].t);
}