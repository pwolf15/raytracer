#include "CppUTest/CommandLineTestRunner.h"

#include "Shape.h"
#include "TestShape.h"
#include "Transformations.h"
#include "Utils.h"

TEST_GROUP(Shape)
{

};

TEST(Shape, Transform)
{
    // Shape s1; // compile error due to abstract class
    TestShape s;
    Matrix identity(
    {
        {1,0,0,0},
        {0,1,0,0},
        {0,0,1,0},
        {0,0,0,1}
    });
    CHECK(identity == s.m_transform);

    Matrix t = translation(2, 3, 4);
    s.set_transform(t);
    CHECK(s.m_transform == t);
}

TEST(Shape, Material)
{
  TestShape s;
  Material m;
  CHECK(Material() == s.m_material);

  m.ambient = 1;
  s.m_material = m;
  CHECK(m == s.m_material);
}

TEST(Shape, Intersect)
{
    // Intersecting a scaled shape with a ray
    Ray r(Point(0,0,-5), Vector(0,0,1));
    std::shared_ptr<TestShape> shape = std::make_shared<TestShape>();
    shape->set_transform(scaling(2,2,2));
    auto xs = intersect(shape, r);

    CHECK(Point(0,0,-2.5) == shape->m_saved_ray.origin);
    CHECK(Vector(0,0,0.5) == shape->m_saved_ray.direction);

    // Intersecting a translated shape with a ray
    shape->m_transform = translation(5,0,0);
    xs = intersect(shape, r);
    CHECK(Point(-5,0,-5) == shape->m_saved_ray.origin);
    CHECK(Vector(0,0,1) == shape->m_saved_ray.direction);
}